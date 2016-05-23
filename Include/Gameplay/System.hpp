#pragma once

#include "Gameplay/Orbiter.hpp"
#include "Utility/Context.hpp"

#include <vector>
#include <array>

class System
{
public:
	System(Context& ctx, const sf::View& view, const std::string& path);

	void update(const float dt);
	void draw(sf::RenderTarget& tgt) const noexcept;


	const sf::FloatRect& getBounds() const noexcept;

	void setUpBorders();

	float getRadius() const noexcept;

	sf::Vector2f getCenter() const noexcept;

private:
	Context& ctx;
	const sf::View& currentView;

	sf::FloatRect bounds;

	std::array<sf::RectangleShape, 4u> borders;
	std::vector<Orbiter> objects;
};
