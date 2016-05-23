#include "Gameplay/Entity.hpp"

Entity::Entity(const sf::Texture& tex) noexcept
: sprite{ tex }
{
}

Entity::Entity(const sf::Texture& tex, const sf::IntRect& texRect) noexcept
: sprite{ tex, texRect }
{
}

void Entity::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();
	tgt.draw(sprite, states);
}

void Entity::setTexture(const sf::Texture& tex, bool resetRectangle) noexcept
{
	sprite.setTexture(tex, resetRectangle);
}

void Entity::setTextureRect(const sf::IntRect& ir) noexcept
{
	sprite.setTextureRect(ir);
}

sf::FloatRect Entity::getLocalBounds() const noexcept
{
	return sprite.getLocalBounds();
}

sf::FloatRect Entity::getGlobalBounds() const noexcept
{
	return getTransform().transformRect(sprite.getGlobalBounds());
}
