#pragma once

#include <SFML/Graphics.hpp>


class AnimatedSprite : public sf::Transformable, public sf::Drawable
{
public:
	AnimatedSprite() = default;
	AnimatedSprite(const sf::Texture& spriteSheet, uint32_t framesCount, const sf::Time& animTime);

	void update(const float dt);

	void create(const sf::Texture& spriteSheet, uint32_t framesCount, const sf::Time& animTime);

    void centerOrigin();

private:
	void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;

	sf::Sprite sprite;
	sf::IntRect currentTextureRect;
	uint32_t keyFrameCount{ 1 }, currentFrame{ 0 };

	sf::Clock clock;

	sf::Time currentTime{ sf::Time::Zero }, animTime{ sf::seconds(1) };
};
