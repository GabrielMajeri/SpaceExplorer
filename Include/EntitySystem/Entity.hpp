#pragma once
#include "Common.hpp"
#include "Component.hpp"

constexpr size_t cMaxComponents{ 16 }, cMaxGroups{ 16 };

using ComponentBitset = std::bitset<cMaxComponents>;
using ComponentArray = std::array<Component*, cMaxComponents>;

using Group = size_t;
using GroupBitset = std::bitset<cMaxGroups>;

class EntityManager;

class Entity final : private NonCopyable {
public:
	explicit Entity(EntityManager& manager) noexcept;

	void update(const sf::Time& dt) noexcept;
	void render(sf::RenderTarget& t) const noexcept;

	void destroy() noexcept;
	bool isDestroyed() const noexcept;

	template <typename Comp>
	bool hasComponent() const noexcept;

	template <typename Comp, typename... Args>
	Comp& addComponent(Args&&... args) noexcept;

	template <typename Comp>
	Comp& getComponent() const noexcept;

	bool hasGroup(Group grp) const noexcept;

	void addGroup(Group grp) noexcept;
	void removeGroup(Group grp) noexcept;
private:
	EntityManager& mManager;

	std::vector<std::unique_ptr<Component>> mComponents;
	ComponentBitset mComponentMarkers;
	ComponentArray mComponentArray;

	GroupBitset mGroupBitset;

	bool mIsDestroyed{ false };
};

template<typename Comp>
inline bool Entity::hasComponent() const noexcept
{
	return mComponentMarkers[getComponentTypeID<Comp>()];
}

template<typename Comp, typename... Args>
inline Comp& Entity::addComponent(Args&& ...args) noexcept
{
	assert(!hasComponent<Comp>());
	Comp* component{ new Comp(std::forward<Args>(args)...) };

	component->mOwner = this;

	mComponents.emplace_back(component);

	mComponentArray[getComponentTypeID<Comp>()] = component;
	mComponentMarkers[getComponentTypeID<Comp>()] = true;

	component->init();

	return *component;
}

template<typename Comp>
inline Comp& Entity::getComponent() const noexcept
{
	assert(hasComponent<Comp>());
	return *reinterpret_cast<Comp*>(mComponentArray[getComponentTypeID<Comp>()]);
}
