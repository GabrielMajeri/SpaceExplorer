#pragma once
#include "Global.h"

class Entity {
public:
	virtual void update(const sf::Time & dt) = 0;
	virtual void draw(sf::RenderTarget & t) = 0;
};

using EntityPtr = std::unique_ptr<Entity>;