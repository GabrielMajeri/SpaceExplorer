#pragma once

#include "World/GameEntity.h"

class Missile : public Entity {
public:
	Missile(const sf::Texture & tex, const sf::Vector2f & pos);

	bool visible;

	void update(const sf::Time & dt) override;
	void draw(sf::RenderTarget & t) override;

	void launch(const sf::Vector2f & pos, const float & rot);

	const sf::Vector2f & getPosition() const { return mSprite.getPosition(); }

private:
	sf::Sprite mSprite;
	sf::Vector2f mVel;
	float mRot{ 0 };
	float mAcc{ 15.0f };
};