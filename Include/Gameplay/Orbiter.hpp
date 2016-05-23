#pragma once

#include "Entity.hpp"

class Context;

/// An Orbiter represents a planet, a star, some body that orbits around another.
/// The body to orbit can be set to nullptr, and in that case this will be static.
/// The parameters a, b control the ellipse's size.
/// This entity may also have a label that is shown floating above it.
class Orbiter : public Entity
{
public:
	Orbiter(const Context& ctx, const sf::Texture& tex, const std::string& name);

	/// Set the parameters of the orbit
	void setParams(const float a, const float b) noexcept;

	/// Sets the body to orbit, or pass nullptr to disable orbiting
	void setBodyToOrbit(const Orbiter* other) noexcept;

	/// Sets the speed of the orbit
	void setOrbitSpeed(const float spd) noexcept;

	/// Updates this body
	virtual void update(const float dt) override;

	const sf::String& getLabel() const noexcept;

	void rotateOrbit(float rad);

private:
	float a, b, currentPos, speed, areaSpeed{ 1 }, rot{ 0 };

	sf::Vector2f off;

	sf::Text label;

	const Orbiter* orbitBody{ nullptr };

    void updateOffset();
    sf::Vector2f getPositionAt(float deg);

    virtual void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;
};
