#include "Graphics/AnimatedSprite.hpp"

#include <cmath>

AnimatedSprite::AnimatedSprite(const sf::Texture& spritesheet, uint32_t framesCount, const sf::Time& animTime)
{
	create(spritesheet, framesCount, animTime);
}

void AnimatedSprite::create(const sf::Texture& tex, uint32_t framesCount, const sf::Time& time)
{
	keyFrameCount = framesCount;
	animTime = time;

	sprite.setTexture(tex);

	currentTextureRect.width = tex.getSize().x / keyFrameCount;
	currentTextureRect.height = tex.getSize().y;

	sprite.setTextureRect(currentTextureRect);
}

void AnimatedSprite::update(const float dt)
{
	currentTime += sf::seconds(dt);

	if(currentTime >= animTime)
		currentTime = sf::Time::Zero;

	currentFrame = std::floor(keyFrameCount * (currentTime / animTime));

	currentTextureRect.left = currentFrame * (sprite.getTexture()->getSize().x / keyFrameCount);

	sprite.setTextureRect(currentTextureRect);
}

void AnimatedSprite::centerOrigin()
{
    setOrigin(currentTextureRect.width / 2, currentTextureRect.height / 2);
}

void AnimatedSprite::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();

	tgt.draw(sprite, states);
}
