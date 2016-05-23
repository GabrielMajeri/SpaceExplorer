#pragma once

#include "Gameplay/Entity.hpp"
#include "Utility/Context.hpp"

class Spaceship final : public Entity
{
public:
	Spaceship(Context& ctx, const sf::Texture& tex);

	void update(const float dt) override;

	void applyForce(sf::Vector2f force);
	void applyForcePolar(float direction, float force);

	void stop();

	const sf::Vector2f& getAccel() const noexcept;
	float getAccelAbs() const noexcept;

	void setControlsActive(bool active);
private:
	bool controlsActive{ true };

	Context& ctx;
	sf::IntRect stillRect, movingRect;

	sf::Vector2f accel{ 0, 0 };
	float rotAccel{ 0 };

	const float maxVelocity, damping;
	float mass, enginePower, thrusterPower;

};
