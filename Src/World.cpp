#include "World.h"

World::World(sf::RenderWindow & window)
: mWindow{window}
{
    std::unique_ptr<CircleShapeNode> p{ new CircleShapeNode { 30.0f } };
    mRoot.addChild(std::move(p));
}


void World::update(const sf::Time & dt)
{
    mRoot.update(dt);
}

void World::draw() const
{
    mWindow.draw(mRoot);
}
