#include "Common.hpp"
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityManager.hpp"

Entity::Entity(EntityManager & manager) noexcept
	: mManager{ manager }
{
}

void Entity::update(const sf::Time& dt) noexcept
{
	for (auto& component : mComponents)
		component->update(dt);
}

void Entity::render(sf::RenderTarget& t) const noexcept
{
	for (const auto& component : mComponents)
		component->render(t);
}

void Entity::destroy() noexcept
{
	mIsDestroyed = true;
}

bool Entity::isDestroyed() const noexcept
{
	return mIsDestroyed;
}

bool Entity::hasGroup(Group grp) const noexcept
{
	return mGroupBitset[grp];
}

void Entity::addGroup(Group grp) noexcept
{
	assert(!mGroupBitset[grp]);
	mGroupBitset[grp] = true;
	mManager.addToGroup(this, grp);
}

void Entity::removeGroup(Group grp) noexcept
{
	assert(mGroupBitset[grp]);
	mGroupBitset[grp] = false;
	mManager.addToGroup(this, grp);
}
