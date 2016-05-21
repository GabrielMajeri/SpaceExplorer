#include "Gameplay/Spaceship.hpp"

#include "Utility/Tools.hpp"

Spaceship::Spaceship(Context& ctx, const sf::Texture& tex)
: Entity{ tex }, ctx{ ctx },
stillRect(0, 0, tex.getSize().x / 2, tex.getSize().y),
movingRect(tex.getSize().x / 2, 0, tex.getSize().x / 2, tex.getSize().y),
maxVelocity{ ctx.om.getFloat("Nava_VitezaMax") },
damping{ ctx.om.getFloat("Nava_Incetinire") },
mass{ ctx.om.getFloat("Nava_Masa") },
enginePower{ ctx.om.getFloat("Nava_PutereMotor") },
thrusterPower{ ctx.om.getFloat("Nava_PutereRotire") }
{
	sprite.setTextureRect(stillRect);
	sprite.setOrigin(stillRect.width / 2, stillRect.height / 2);
}

void Spaceship::applyForce(sf::Vector2f force)
{
    accel += force / mass;
}

void Spaceship::applyForcePolar(float direction, float force)
{
	accel.x += (force * std::cos(direction)) / mass;
	accel.y += (force * std::sin(direction)) / mass;
}

void Spaceship::update(const float dt)
{
	bool isMoving = false;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		applyForcePolar(Utility::toRadians(getRotation()), enginePower * dt);
		isMoving = true;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		applyForcePolar(Utility::toRadians(getRotation()), -enginePower * dt);
		isMoving = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotAccel += thrusterPower * dt / mass;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotAccel -= thrusterPower * dt / mass;
	}

	sprite.setTextureRect(isMoving ? movingRect : stillRect);

	accel.x = Utility::clamp(accel.x, -maxVelocity, +maxVelocity);
	accel.y = Utility::clamp(accel.y, -maxVelocity, +maxVelocity);

	accel *= damping;

	move(accel);

	rotAccel *= damping;
	rotate(rotAccel);
}

void Spaceship::stop()
{
    accel = { 0, 0 };
    rotAccel = 0;
}
