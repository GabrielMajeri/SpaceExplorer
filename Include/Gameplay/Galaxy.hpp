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
	int32_t currentSystemView{ -1 };

	sf::FloatRect bounds;

	sf::View currentView;
	float viewZoom{ 1 };

	Starfield backgroundStars;

	std::unique_ptr<Spaceship> spaceship;

	struct SystemView
	{
		SystemView(Context& ctx, sf::Texture& tex, const std::string& label, const std::string& description, int32_t pos);

		Orbiter view;
		int32_t assocSystem;

		sf::String description;
	};

	std::vector<std::unique_ptr<System>> systems;
	std::vector<SystemView> systemViews;

	std::array<sf::RectangleShape, 4u> borders;

	sf::Text enterSystemInfo, systemDescription;
	float diagonal;

	sf::RectangleShape descBackground;
	bool nearEntrypoint{ false }, nearSystem{ false };

	void recalculateView();
	void setUpBorders();
	void rescaleUI();

	void moveIntoSystem(int32_t current, int32_t viewPos);
	void leaveSystem();
};
