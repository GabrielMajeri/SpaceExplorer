#include "Player/Player.h"

Player::Player(World & w, bool * keys, const Spaceship & ship)
	: mWorld{ w },
	mKeys{ keys }, 
	mKeyBinds{},
	mShip{ ship }
{
	
}

void Player::update(const sf::Time & dt)
{
	mShip.forward = mKeys[mKeyBinds.getKey("player_forward")];
	mShip.left = mKeys[mKeyBinds.getKey("player_left")];
	mShip.backward = mKeys[mKeyBinds.getKey("player_backward")];
	mShip.right = mKeys[mKeyBinds.getKey("player_right")];

	if (cooldown == 0 && mKeys[mKeyBinds.getKey("player_shoot")] == true) {
		mShip.launchMissile();
		cooldown = 120;
	}

	if (cooldown > 0)
		cooldown--;

	mShip.update(dt);

	mWorld.getView().setCenter(mShip.getPosition());

	if (mShip.isMoving && mShip.forward) {
		if (mWorld.getView().getSize().x < mWorld.getWindow().getWidth() * 1.5f)
			mWorld.getView().zoom(1.01f);
	} else {
		if (mWorld.getView().getSize().x > mWorld.getWindow().getWidth() * 0.5f)
			mWorld.getView().zoom(0.99f);
	}
}

void Player::draw(sf::RenderTarget & t)
{
	mShip.draw(t);
}