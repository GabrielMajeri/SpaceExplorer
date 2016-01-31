#pragma once
#include "Global.h"
#include "World/GameEntity.h"
#include "Missile.h"

class Spaceship : public Entity {
public:
	Spaceship(const sf::Vector2f & pos, 
		const sf::Texture & shipTex,
		const sf::Texture & missileTex);

	virtual void update(const sf::Time & dt) override;
	virtual void draw(sf::RenderTarget & t) override;

	bool forward, backward, left, right;
	bool isMoving;

	sf::Vector2f getPosition() const;

	void launchMissile();

	friend float distance(const Spaceship&, const Missile&);
private:
	sf::Sprite mSprite;

	sf::Vector2f mVel{ 0.0f, 0.0f };
	float mAcc{ 10.0f };

	float mRot{ 0.0f }, mRotVel{ 0.0f }, mRotAcc{ 35.0f };

	float backPenalty{ 0.75f };
	
	float mDamp{ 0.9905f }, mRotDamp{ 0.9505f };

	// Missiles
	std::vector<Missile> mMissiles;
};