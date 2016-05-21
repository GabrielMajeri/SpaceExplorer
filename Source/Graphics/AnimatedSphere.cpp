#include "Graphics/AnimatedSphere.hpp"


AnimatedSphere::AnimatedSphere(sf::Texture& tex, float radius, const sf::Time& time)
{
    create(tex, radius, time);
}

void AnimatedSphere::create(sf::Texture& tex, float radius, const sf::Time& time)
{
	circle.setTexture(&tex);
	tex.setRepeated(true);

	if(radius < 0)
		throw std::logic_error{ "Circle's radius cannot be negative! Radius = " + std::to_string(radius) };

	float diam = 2 * radius;
	texRect = { 0, 0, (int)diam, (int)diam };

	circle.setRadius(radius);

	passed = sf::Time::Zero;
	animTime = time;

	texRect = { 0, 0, 2 * (int)radius, 2 * (int)radius };
	circle.setTextureRect(texRect);
}

#include <iostream>
void AnimatedSphere::update(const float dt)
{
	passed += sf::seconds(dt);

	if(passed > animTime)
		passed = sf::Time::Zero;

    texRect.left = std::floor(float(passed / animTime) * (texRect.width << 1));

	circle.setTextureRect(texRect);
}

void AnimatedSphere::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();

	tgt.draw(circle, states);
}

void AnimatedSphere::centerOrigin()
{
    setOrigin(circle.getLocalBounds().width / 2.f, circle.getLocalBounds().height / 2.f);
}

float AnimatedSphere::getRadius() const noexcept
{
	return circle.getRadius();
}
