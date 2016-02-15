#pragma once
#include "Common.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Component.hpp"

/// This component allows an entity to have a transform in 2D space. This component
/// does not care about units of measurement.
class CTransformable final : public Component, public sf::Transformable {
public:
	/// Constructs a new component with position at (0, 0)
	explicit CTransformable() = default;
	/// Deletes this component
	~CTransformable() = default;

	/// Constructs a new component from a given position
	explicit CTransformable(const sf::Vector2f& pos) noexcept { setPosition(pos); }
	explicit CTransformable(sf::Vector2f&& pos) noexcept { setPosition(std::move(pos)); }
};