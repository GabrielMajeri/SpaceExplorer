#pragma once

#include "Gameplay/Orbiter.hpp"
#include "Utility/Context.hpp"
#include "Utility/NonCopyable.hpp"

#include <vector>
#include <array>
#include <memory>

class Galaxy;

class System : public NonCopyable
{
public:
	System(Context& ctx, const sf::View& view, Galaxy& galaxy, const std::string& path);

	void update(const float dt);
	void draw(sf::RenderTarget& tgt) const noexcept;

	const sf::FloatRect& getBounds() const noexcept;

	void setUpBorders();

	float getRadius() const noexcept;

	sf::Vector2f getCenter() const noexcept;

	void recalculateGUI(uint32_t textSize) noexcept;

private:
	Context& ctx;
	Galaxy& galaxy;
	const sf::View& currentView;

	sf::FloatRect bounds;

	std::array<sf::RectangleShape, 4u> borders;
	std::vector<std::unique_ptr<Orbiter>> objects;

	sf::RectangleShape textBackground;
	bool nearPlanet{ false };
	sf::Text descript;
};
