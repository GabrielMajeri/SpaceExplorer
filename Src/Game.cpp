#include "Game.h"

// Constructor
Game::Game()
: mWindow {
    // The width and height of the window
    sf::VideoMode{ 800, 600 },
    // The title of this window
    "Space Explorer"
    },
    mWorld{mWindow}
{
    // TODO: initialize stuff
}


void Game::run()
{
    mFrameClock.restart();
    while(mIsRunning == true) {
        handleEvents();

        update(FrameTimeTarget);

        render();
    }
}

void Game::handleEvents()
{
    // Retrieves events from the event pump
    while(mWindow.pollEvent(mEvent)) {
        // Handles events based on their type
        switch (mEvent.type) {
            // If the user closed the window
            case sf::Event::Closed:
                closeGame();
                return;
            // If the user resized the window
            case sf::Event::Resized:
                handleResize(mEvent);
                return;
            default:
                return;
        }
    }
}

void Game::closeGame()
{
    mIsRunning = false;
    mWindow.close();
}

void Game::handleResize(const sf::Event & e)
{
    // TODO: store new W/H in Vector2u
    mWindow.setSize({e.size.width, e.size.height});
}

void Game::update(const sf::Time & dt)
{
    mWorld.update(dt);
}

void Game::render()
{
    mWindow.clear();

    mWorld.draw();

    mWindow.display();
}
