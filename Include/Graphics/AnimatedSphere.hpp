#pragma once

#include <SFML/Graphics.hpp>

/// This class simulates an animated sphere. It takes a texture rectangle and clips
/// it on a circle. Can be used for stars, planets, asteroids etc.
/// For more general animations use AnimatedSprite
class AnimatedSphere : public sf::Transformable, public sf::Drawable
{
public:
	AnimatedSphere() = default;
	AnimatedSphere(sf::Texture& tex, float radius, const sf::Time& animTime);

	void create(sf::Texture& tex, float radius, const sf::Time& animTime);

	void update(const float dt);

	void centerOrigin();

	float getRadius() const noexcept;

private:
	void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;

	sf::CircleShape circle;
	sf::IntRect texRect;
	sf::Time passed, animTime;
};
