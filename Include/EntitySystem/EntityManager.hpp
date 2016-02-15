#pragma once
#include "Common.hpp"
#include "Entity.hpp"

/// The entity manager is the owner of all the entities in the game world,
/// and is responsible for their lifetime and destruction. The manager draws,
/// updates and adds / removes entities.
class EntityManager final : private NonCopyable {
public:
	/// Construct a new entity manager
	explicit EntityManager() noexcept = default;

	/// Updates all the entities
	void update(const sf::Time& dt) noexcept; 
	/// Renders all the entities
	void render(sf::RenderTarget& t) const noexcept;
	
	/// Adds an entity to the world
	Entity& addEntity() noexcept;

	/// Adds a specified entity to a group
	void addToGroup(Entity* entity, Group grp) noexcept;
	std::vector<Entity*>& getGroup(Group grp) noexcept;
	const std::vector<Entity*>& getGroup(Group grp) const noexcept;

	/// Deletes destroyed entities
	void cleanup() noexcept;

	enum EntityGroup : Group {
		Drawable, Collisionable
	};
private:
	/// This vector owns all the entities
	std::vector<std::unique_ptr<Entity>> mEntities{ };
	/// The entities are stored in buckets to easily be obtained
	std::array<std::vector<Entity*>, cMaxGroups> mGroupedEntities{ };
};