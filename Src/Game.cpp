#include "Game.h"

// Constructor
Game::Game()
: mWindow {
    // The width and height of the window
    sf::VideoMode{ 800, 600 },
    // The title of this window
    "Space Explorer"
    }
{
    // TODO: initialize stuff

    mTextures.loadFromFile("stars", "Resources/Textures/background.png");

    mTextures.loadFromFile("ship", "Resources/Textures/spaceship.png");

    mBackground.setTexture(mTextures.getResource("stars"));
    mPlayer.setTexture(mTextures.getResource("ship"));

    mWindow.setFramerateLimit(60);

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
            case sf::Event::KeyPressed:
                handleKeyboard(mEvent, true);
                return;
            case sf::Event::KeyReleased:
                handleKeyboard(mEvent, false);
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

void Game::handleKeyboard(const sf::Event & e, const bool & state)
{
    keys[e.key.code] = state;
}

void Game::update(const sf::Time & dt)
{
    float s = sin(rotation), c = cos(rotation);

    if(keys[sf::Keyboard::W])
        mPlayer.move(mSpeed.x*s - mSpeed.y*s, mSpeed.x*s + mSpeed.y*c);
}

void Game::render()
{
    mWindow.clear();

    mWindow.draw(mBackground);

    mWindow.draw(mPlayer);

    mWindow.display();
}
