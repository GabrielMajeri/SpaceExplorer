#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "ResourceHolder.h"

/**
* This is Space Explorer's main class. It controls the
* game's window and connects the various subsystems.
*
* @author Gabriel
*/
class Game
{
// Public functions
public:
    Game();

    /// Run is called when game is started
    void run();

// Member variables
private:
    /// This is the game's main window
    sf::RenderWindow mWindow;

    /// Controls the game's loop
    bool mIsRunning;

    /// Used for precise frame timing
    sf::Clock mFrameClock;

    /// Frame time limit
    const sf::Time FrameTimeTarget{ sf::seconds(1.0f / 60.0f) };

    /// Temporary variable to store events from the stack
    /// before they are handled
    sf::Event mEvent;

    TextureHolder mTextures;

    //
    sf::Sprite mBackground;

    sf::Sprite mPlayer;
    sf::Vector2f mSpeed{1.0f, 0.0f};
    float rotation;

    bool keys[512];

// Member functions
private:
    /// Handle events fills the event queue
    void handleEvents();

    /// Update does numerical integration by simulating one step of the game world
    void update(const sf::Time & dt);

    /// Render draws the screen
    void render();

    void closeGame();
    void handleResize(const sf::Event & e);
    void handleKeyboard(const sf::Event & e, const bool & state);
};
