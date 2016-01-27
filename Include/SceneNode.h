#pragma once

#include <memory>
#include <vector>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

/**
* The world is stored as a graph. Each node either is
* an object in the world or has children.
* Each node has a transform.
*
* @author Gabriel
*/
class SceneNode
: private sf::NonCopyable,
  public sf::Transformable,
  public sf::Drawable
{
public:
    /// Using unique pointers to guarantee proper deallocation
    using NodePtr = std::unique_ptr<SceneNode>;

public:
    /// Constructs a new node with nullptr as its parent
    SceneNode();

    /// Functions to add and remove children of this node
    void addChild(NodePtr child);
    NodePtr removeChild(const SceneNode & child);

    /// Updates this node and all its children
    void update(const sf::Time & dt);

    /// Gets the transform relative to the root node
    sf::Transform getWorldTransform() const;
    /// Gets the position relative to the root node
    sf::Vector2f getWorldPosition() const;

private:
    /// This is a pointer to this node's parent
    SceneNode * mParent;

    /// This contains pointers to all the children
    /// A node may not have 2 parents
    std::vector<NodePtr> mChildren;

private:
    /// This function draws this node and all its children
    /// This overrides Drawable's pure virtual function
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void updateCurrent(const sf::Time & dt);
    void updateChildren(const sf::Time & dt);
};
