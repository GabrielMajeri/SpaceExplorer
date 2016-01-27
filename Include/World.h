#pragma once

#include "SceneNode.h"
#include "SpriteNode.h"
#include "CircleShapeNode.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>


// Forward declare sf::RenderWindow
namespace sf
{ class RenderWindow; }


/**
* This class contains information on the level, the player, the scene node.
* It interacts with the Game class.
*
* @author Gabriel
*/
class World
{
public:
    /// Constructs a new, empty world
    World(sf::RenderWindow & window);

    /// Moves the world through another step
    void update(const sf::Time & dt);

    /// Draws to screen
    void draw() const;

private:
    /// The root of the scene graph
    SceneNode mRoot;

    /// Reference to the window
    sf::RenderWindow & mWindow;
};
