#pragma once
#include "Common.hpp"

class Entity;

/// A component that is owned by an entity. Components give entities functionality,
/// while being fully decoupled.
class Component : public NonCopyable {
	friend class Entity;
public:
	/// Constructs a new component.
	explicit Component() noexcept = default;
	/// Virtual destructor for extended classes.
	virtual ~Component() = default;

	/// Inits this component
	virtual void init() noexcept {};
	/// Updates this component
	virtual void update(const sf::Time& dt) noexcept {};
	/// Draws this component
	virtual void render(sf::RenderTarget& t) const noexcept {};

protected:
	/// The owner of this component
	Entity* mOwner;
};

/// The ID of a component is simply a natural number
using ComponentID = size_t;

namespace Internal {
	/// This lambda returns a different number each time it's called.
	inline ComponentID getUniqueID() noexcept
	{
		static ComponentID lastUsedID{ 0u };
		return lastUsedID++;
	}
}

/// This template will be expanded once for every type of component, guaranteeing
/// no two components will have the same ID.
template <typename Comp>
inline ComponentID getComponentTypeID() noexcept
{
	// Only components can have an ID.
	static_assert(std::is_base_of<Component, Comp>::value, "Tried to get ID of non-component.");

	// The ID is static in order to be the same for every instance of the component.
	static ComponentID ID{ Internal::getUniqueID() };

	return ID;
}