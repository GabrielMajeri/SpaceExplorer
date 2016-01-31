#include "Game.h"

Game::Game()
	: mWindow{ 800, 600, "Space Explorer", 120, 8 },
	mWorld{ mWindow, mKeys }
{
	std::fill(std::begin(mKeys), std::end(mKeys), false);

	mWindow.setEventHandleCallback(std::bind(&Game::handleInput, this, std::placeholders::_1));
	mWindow.setUpdateCallback(std::bind(&Game::update, this, std::placeholders::_1));
	mWindow.setDrawCallback(std::bind(&Game::draw, this, std::placeholders::_1));
	mWindow.setVSync(false);

	mFont.loadFromFile("Resources/Fonts/Arial.ttf");
	mText.setCharacterSize(20);
	mText.setPosition({ 10, 15 });
	mText.setFont(mFont);
}

void Game::run()
{
	mWindow.start();
}

void Game::handleInput(const sf::Event & e)
{
	switch (e.type) {
	case sf::Event::Closed:
		mWindow.stop();
		return;
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Escape)
			mWindow.stop();
		mKeys[e.key.code] = true;
		return;
	case sf::Event::KeyReleased:
		mKeys[e.key.code] = false;
		return;
	default:
		return;
	}
}

void Game::update(const sf::Time & dt)
{
	mWorld.update(dt);

	mText.setString("FPS: " + std::to_string(mWindow.getLastFPS()) + "\nUPS: " +
		std::to_string(mWindow.getLastUPS()));
}

void Game::draw(sf::RenderTarget & t)
{
	mWorld.draw(t);
	t.setView(t.getDefaultView());
	t.draw(mText);
}
