#pragma once

#include "Gameplay/Orbiter.hpp"
#include "Utility/Context.hpp"

class System
{
public:
	System(Context& ctx, const std::string& path);

	void draw(sf::RenderTarget& tgt) const noexcept;

private:
	Context& ctx;

	std::vector<Orbiter> objects;
};
