#pragma once
#include "Common.hpp"
#include "CTransformable.hpp"
#include "EntitySystem/Entity.hpp"

/// This component allows an entity with a position to have a velocity.
class CVelocity final : public Component {
public:
	/// Constructs a new entity with no velocity
	CVelocity() = default;
	/// Destructs the entity
	~CVelocity() = default;

	/// Constructs an entity with a specified velocity
	CVelocity(const sf::Vector2f& v) : mVelocity{ v } {}
	CVelocity(sf::Vector2f&& v) : mVelocity{ std::move(v) } {}
	
	/// Initializes the pointer to the owner's position component
	void init() noexcept override 
	{
		mTransformableComponent = &mOwner->getComponent<CTransformable>();
	}

	/// Moves the entity.
	void update(const sf::Time& dt) noexcept override
	{ 
		// dx / dt = v, therefore dx = v * dt
		mTransformableComponent->move (mVelocity * dt.asSeconds());
	}

	/// The current velocity
	sf::Vector2f mVelocity{ 0.f, 0.f };
	/// The position to update
	CTransformable* mTransformableComponent{ nullptr };
};