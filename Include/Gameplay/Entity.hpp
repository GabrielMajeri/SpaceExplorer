#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity() = default;
	Entity(const sf::Texture& tex);

	virtual ~Entity() = default;

	void setTexture(const sf::Texture& tex);
	void setTextureRect(const sf::IntRect& ir);

	virtual void update(const float dt) = 0;

	sf::FloatRect getLocalBounds() const noexcept;
	sf::FloatRect getGlobalBounds() const noexcept;

protected:
    sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;
};
