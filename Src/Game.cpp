#include "Game.h"

#include <iostream>

#define PI 3.1415f

const unsigned int mWidth = 800, mHeight = 600;

// Constructor
Game::Game()
: mWindow {
    // The width and height of the window
    sf::VideoMode{ mWidth, mHeight },
    // The title of this window
    "Space Explorer"
    },
    mView{
        {mWidth / 2, mHeight / 2},
        {mWidth, mHeight}
    }
{
    std::fill(std::begin(keys), std::end(keys), false);

    mTextures.loadFromFile("stars", "Resources/Textures/background.png");
    mTextures.loadFromFile("ship_stopped", "Resources/Textures/spaceship1.png");
    mTextures.loadFromFile("ship_started", "Resources/Textures/spaceship2.png");
    mTextures.getResource("ship_stopped").setSmooth(true);
    mTextures.getResource("ship_started").setSmooth(true);
    mTextures.getResource("stars").setSmooth(true);
    mTextures.getResource("stars").setRepeated(true);


    mBackground.setTexture(mTextures.getResource("stars"));
    mBackground.setTextureRect({0, 0, mWidth * 100, mHeight * 100});
    mBackground.setOrigin(mBackground.getTextureRect().width / 2, mBackground.getTextureRect().height / 2);

    mPlayer.setTexture(mTextures.getResource("ship_stopped"));

    mWindow.setFramerateLimit(60);

    mPlayer.setOrigin(mPlayer.getTextureRect().width / 2, mPlayer.getTextureRect().height / 2);
    mPlayer.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
    mView.zoom(0.75f);
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
    if(keys[sf::Keyboard::Escape])
        mIsRunning = false;

    if(keys[sf::Keyboard::W])
        velocity += {accel * (float)cos(rotation), accel * (float)sin(rotation)};

    if(keys[sf::Keyboard::S])
        velocity += {- accel * (float)cos(rotation), - accel * (float)sin(rotation)};

    if(keys[sf::Keyboard::A])
        rotation -= 0.1f;
    if(keys[sf::Keyboard::D])
        rotation += 0.1f;

    if(abs(velocity.x) > 0) {
        velocity.x *= damp;
        mPlayer.setTexture(mTextures.getResource("ship_started"));
    } else mPlayer.setTexture(mTextures.getResource("ship_stopped"));

    if(abs(velocity.y) > 0){
        velocity.y *= damp;
        mPlayer.setTexture(mTextures.getResource("ship_started"));
    } else mPlayer.setTexture(mTextures.getResource("ship_stopped"));

    //if(abs(velocity.x) < 0.01f && abs(velocity.y) < 0.01f)
        //velocity.x = 0, velocity.y = 0;

    if(keys[sf::Keyboard::Space])
        velocity.x *= 0.75f, velocity.y *= 0.75f;

    position += velocity;
    mPlayer.setPosition(position);
    mPlayer.setRotation(rotation * 180.f / PI);

    mView.setCenter(mPlayer.getPosition());
}

void Game::render()
{
    mWindow.clear();

    mWindow.draw(mBackground);

    mWindow.draw(mPlayer);

    mWindow.setView(mView);

    mWindow.display();
}
