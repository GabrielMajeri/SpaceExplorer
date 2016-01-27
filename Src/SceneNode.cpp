#include "SceneNode.h"

SceneNode::SceneNode()
 : mParent{ nullptr },
 mChildren{ }
{

}

void SceneNode::addChild(NodePtr child)
{
    // The child's parent is this node
    child->mParent = this;

    // The parent receives ownership of the child
    // and adds the child to its children.
    mChildren.push_back(std::move(child));
}


SceneNode::NodePtr SceneNode::removeChild(const SceneNode & child)
{
    // Go through the vector and search for the child
    // Search result is an iterator to the found element
    auto searchResult = find_if(mChildren.begin(), mChildren.end(),
                                [&child](NodePtr & p) -> bool { return (p.get() == &child); });

    // Move the unique ptr from the children vector to a temporary variable
    NodePtr ret = std::move(*searchResult);

    // The node will no longer know this node as its parent
    ret->mParent = nullptr;

    // Remove the node from the node vector
    mChildren.erase(searchResult);

    // When returning ret, it will be released automatically
    return ret;
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    // Combines the transforms with this node's relative one
    states.transform.combine(getTransform());

    // Draws the current node
    drawCurrent(target, states);

    // Go through each child
    for(const auto & child : mChildren)
        // Recursively have each child draw itself
        child->draw(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    // Do nothing, scene nodes do not get draw by default
}

void SceneNode::update(const sf::Time & dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(const sf::Time & dt)
{
    // Do nothing, scene nodes do not get updated by default
}

void SceneNode::updateChildren(const sf::Time & dt)
{
    for(auto & child : mChildren)
        child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform ret = sf::Transform::Identity;

    for(const SceneNode * p = this; p != nullptr; p = p->mParent)
        ret = p->getTransform() * ret;

    return ret;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform().transformPoint(0, 0);
}
