#pragma once
#include "Global.h"
#include "World/GameEntity.h"
#include "World/World.h"
#include "KeyBindings.h"
#include "Spaceships/Spaceship.h"

class Player final : public Entity, private sf::NonCopyable {
public:
	Player(World & w, bool * keys, const Spaceship & ship);

	void update(const sf::Time & dt) override;
	void draw(sf::RenderTarget & t) override;

private:
	World & mWorld;
	bool * mKeys;
	KeyBinds mKeyBinds;

	float cooldown{ 0 };

	Spaceship mShip;
};