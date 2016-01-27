#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "SceneNode.h"

/**
* This class represents a drawable circle scene node.
* Only to be used for testing.
* @author Gabriel
*/
class CircleShapeNode
 : public SceneNode
{
public:
    /// Constructs a new circle shape node.
    CircleShapeNode(const float & radius, const size_t & nrOfPoints = 30);

private:
    /// The actual circle that is stored.
    sf::CircleShape mCircle;

    /// Draws the circle to the screen.
    virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const override;
};
