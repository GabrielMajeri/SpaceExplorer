#pragma once

#include "Gameplay/Orbiter.hpp"
#include "Utility/Context.hpp"

class System
{
public:
	System(Context& ctx, const std::string& path);

	void draw(sf::RenderTarget& tgt) const noexcept;

	const sf::FloatRect& getBounds() const noexcept;

private:
	Context& ctx;

	sf::FloatRect bounds;

	std::vector<Orbiter> objects;
};
