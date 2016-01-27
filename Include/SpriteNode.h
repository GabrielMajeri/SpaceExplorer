#pragma once

#include "SceneNode.h"

#include <SFML\Graphics.hpp>

/**
* This class represents a sprite scene node.
*
* @author Gabriel
*/
class SpriteNode
: public SceneNode
{
public:
    SpriteNode(const sf::Texture & tex);
    SpriteNode(const sf::Texture & tex, const sf::IntRect rect);

private:
    /// The sprite to be drawn on screen
    sf::Sprite mSprite;

    /// The function that draws the sprite
    virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const override;
};
