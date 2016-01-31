#include "..\..\Include\Spaceships\Missile.h"

Missile::Missile(const sf::Texture & tex, const sf::Vector2f & pos)
	: mSprite{ tex },
	visible{ false }
{
	mSprite.setPosition(pos);
}

void Missile::update(const sf::Time & dt)
{
	if (visible == false)
		return;

	mVel += {cos(mRot) * mAcc * dt.asSeconds(), sin(mRot) * mAcc * dt.asSeconds()};

	mVel *= 0.97f;

	mSprite.move(mVel);

	mSprite.setRotation(mRot * 180.f / M_PI);
}

void Missile::draw(sf::RenderTarget & t)
{
	if (visible == false)
		return;

	t.draw(mSprite);
}

void Missile::launch(const sf::Vector2f & pos, const float & rot)
{
	visible = true;
	mSprite.setPosition(pos);
	mRot = rot;
}
