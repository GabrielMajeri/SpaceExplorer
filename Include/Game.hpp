#pragma once

#include <SFML/Graphics.hpp>
#include "Utility/Context.hpp"
#include "State/StateManager.hpp"

class Game
{
public:
	Game();

	void run();

	void toggleFullscreen();

private:
	Context ctx;
	const sf::ContextSettings settings;
	sf::RenderWindow window;

	// Window variables
	static constexpr uint32_t windowedStyle = sf::Style::Close, fullscreenStyle = sf::Style::Fullscreen;
	bool isFullscreen;

	bool isRunning{ false }, isStandby{ true };

	StateManager states;

	void setWindowOptions();

	void handleEvents();
	void update(const float dt);
	void draw();
};
