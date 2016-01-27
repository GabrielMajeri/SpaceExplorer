#include "CircleShapeNode.h"

CircleShapeNode::CircleShapeNode(const float & radius, const size_t & nrOfPoints)
 : mCircle(radius, nrOfPoints)
{ }

void CircleShapeNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(mCircle, states);
}
