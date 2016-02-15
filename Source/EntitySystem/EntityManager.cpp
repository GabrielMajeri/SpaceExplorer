#include "Common.hpp"
#include "EntitySystem/EntityManager.hpp"

void EntityManager::update(const sf::Time& dt) noexcept
{
	// Iterate through every entity and update it
	for (auto& entity : mEntities)
		entity->update(dt);
}

void EntityManager::render(sf::RenderTarget& t) const noexcept
{
	// Draw every entity each frame
	const auto& drawables{ getGroup(EntityGroup::Drawable) };
	for (const auto& drawable : drawables)
		drawable->render(t);
}

Entity& EntityManager::addEntity() noexcept
{
	// Add a new entity to the world
	mEntities.emplace_back(std::make_unique<Entity>(*this));
	// Return a reference to allow easy modification
	return *mEntities.back();
}

void EntityManager::addToGroup(Entity* entity, Group grp) noexcept
{
	mGroupedEntities[grp].emplace_back(entity);
}

std::vector<Entity*>& EntityManager::getGroup(Group grp) noexcept
{
	return mGroupedEntities[grp];
}

const std::vector<Entity*>& EntityManager::getGroup(Group grp) const noexcept
{
	return mGroupedEntities[grp];
}

void EntityManager::cleanup() noexcept
{
	// Go through each group / type of entity
	for (auto i{ 0u }; i < cMaxGroups; ++i) {
		auto& group{ mGroupedEntities[i] };

		// Remove all entities that are either destroyed or has changed its group
		group.erase(std::remove_if(std::begin(group), std::end(group),
			[i](auto& ptr) -> bool { return ptr->isDestroyed() || !ptr->hasGroup(i); }),
			std::end(group));
	}

	// Erase all entities that have been destroyed from the vector of unique ptrs too.
	// The vector owns the objects, at this point they will be destroyed.
	mEntities.erase(std::remove_if(std::begin(mEntities), std::end(mEntities),
		[](auto& entity) -> bool { return entity->isDestroyed(); }), std::end(mEntities));
}
