#pragma once
#include "Global.h"

#include "Graphics/Window.h"
#include "World/World.h"

class Game : private sf::NonCopyable {
public:
	Game();

	void run();

private:
	Window mWindow;

	World mWorld;

	sf::Font mFont;
	sf::Text mText;

	bool mKeys[2048];

private:
	void handleInput(const sf::Event & e);
	void update(const sf::Time & dt);
	void draw(sf::RenderTarget & t);
};