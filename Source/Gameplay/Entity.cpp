#include "Gameplay/Entity.hpp"

Entity::Entity(const sf::Texture& tex)
: sprite{ tex }
{
}

void Entity::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();
	tgt.draw(sprite, states);
}

sf::FloatRect Entity::getLocalBounds() const noexcept
{
	return sprite.getLocalBounds();
}

sf::FloatRect Entity::getGlobalBounds() const noexcept
{
	return getTransform().transformRect(sprite.getGlobalBounds());
}
