#pragma once

#include "Entity.hpp"

class Context;

class Orbiter : public Entity
{
public:
	Orbiter(const Context& ctx, const sf::Texture& tex, const std::string& name);

	virtual void update(const float dt) override;

private:
	virtual void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;

	sf::Text label;

    float angularVelocity;
};
