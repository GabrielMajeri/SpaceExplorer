#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture & tex)
 : mSprite{ tex }
{

}

SpriteNode::SpriteNode(const sf::Texture & tex, const sf::IntRect rect)
 : mSprite{ tex, rect }
{

}

void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{


}
