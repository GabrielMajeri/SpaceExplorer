#pragma once

#include <string>
#include <array>

#include "Graphics/Starfield.hpp"
#include "Gameplay/Spaceship.hpp"
#include "Gameplay/System.hpp"

struct Context;

class Galaxy
{
public:
	Galaxy(Context& ctx, const std::string& filePath);

	bool inSystem() const noexcept;

	void handleEvent(const sf::Event& e);
	void update(const float dt);
	void draw(sf::RenderTarget& tgt) const noexcept;

private:
	Context& ctx;

	std::string name;
	std::string description;

	int32_t currentSystem{ -1 };

	sf::FloatRect bounds;

	sf::View currentView;
	float viewZoom{ 1 };

	Starfield backgroundStars;

	std::unique_ptr<Spaceship> spaceship;

	struct SystemView
	{
		SystemView(Context& ctx, sf::Texture& tex, const std::string& label, int32_t pos);

		Orbiter view;
		int32_t assocSystem;
	};
	std::vector<System> systems;
	std::vector<SystemView> systemViews;

	std::array<sf::RectangleShape, 4u> borders;

	void recalculateView();

	void setUpBorders();
};
