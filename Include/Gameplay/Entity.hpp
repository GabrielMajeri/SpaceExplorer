#pragma once

#include <SFML/Graphics.hpp>

/// An entity represents an object that is drawn on screen. The entity has
/// an update function that represents a step taken in its internal state.
/// It is doing Euler numerical integration with the dt parameter.
class Entity : public sf::Transformable, public sf::Drawable
{
public:
	/// Constructs a new entity at (0, 0). Does not set its texture
	Entity() noexcept = default;

	/// Constructs a new entity from a texture
	Entity(const sf::Texture& tex) noexcept;

	/// Constructs a new entity from part of a texture
	Entity(const sf::Texture& tex, const sf::IntRect& texRect) noexcept;

	/// Virtual dtor
	virtual ~Entity() = default;

	/// Sets the texture of this sprite, possibly resetting the texture rectangle
	void setTexture(const sf::Texture& tex, bool resetRectangle = false) noexcept;
	/// Sets the sprite's texture rectangle
	void setTextureRect(const sf::IntRect& ir) noexcept;


	/// The update function
	virtual void update(const float dt) = 0;

	/// Gets the bounds of this sprite's texture
	sf::FloatRect getLocalBounds() const noexcept;

	/// Gets the transformed bounding rectangle
	sf::FloatRect getGlobalBounds() const noexcept;

protected:
	/// The sprite used to represent this entity.
    sf::Sprite sprite;

    /// Draws the entity to screen
	virtual void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;
};
