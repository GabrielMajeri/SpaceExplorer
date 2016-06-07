#include "Gameplay/Orbiter.hpp"

#include "Utility/Tools.hpp"
#include "Utility/Context.hpp"

#include <cmath>

Orbiter::Orbiter(const Context& ctx, const sf::Texture& tex, const std::string& name, const std::string& description)
: Entity(tex), description{ Utility::fromUTF8(description) }
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	label.setFont(ctx.fonts["Normal"]);
	label.setString(Utility::fromUTF8(name));

	label.move(0, -sprite.getLocalBounds().height / 1.5);
	Utility::centerText(label);
}

void Orbiter::setParams(const float a, const float b) noexcept
{
	this->a = a;
	this->b = b;
}

void Orbiter::updateOffset()
{
	const auto& pos = orbitBody->getPosition();
	auto fociDistance = std::sqrt(a * a + b * b) / 4.f;

	off = { pos.x - fociDistance * std::cos(rot), pos.y - fociDistance * std::sin(rot) };
}

void Orbiter::setBodyToOrbit(const Orbiter* other) noexcept
{
	orbitBody = other;

	if(other != nullptr)
		updateOffset();
}

void Orbiter::setOrbitSpeed(const float spd) noexcept
{
    speed = spd;
}

void Orbiter::setOrbitRotation(float rad) noexcept
{
	rot = rad;

	updateOffset();
}

void Orbiter::rotateOrbit(float rad)
{
	rot += rad;

	updateOffset();
}

sf::Vector2f Orbiter::getPositionAt(float theta)
{
	const auto cosa = std::cos(rot), sina = std::sin(rot);
	const auto cosb = std::cos(theta), sinb = std::sin(theta);

	const auto x_cs = off.x + (a * cosa * cosb) - (b * sina * sinb);
	const auto y_cs = off.y + (a * cosa * sinb) + (b * sina * cosb);

	return { x_cs, y_cs };
}


void Orbiter::update(const float dt)
{
	if(orbitBody != nullptr)
	{
		updateOffset();

		currentPos += areaSpeed * speed * dt;
		currentPos = Utility::clamp(currentPos, -360, 360);

        sf::Vector2f newPos{ getPositionAt(currentPos + dt) };

        const auto& orbPos = orbitBody->getPosition();

		float radius = Utility::abs(orbPos - newPos);
        areaSpeed = 1000000.f / (Utility::PI<float> * radius * radius);

		setPosition(getPositionAt(currentPos));
	}
}

void Orbiter::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();

	tgt.draw(sprite, states);
	tgt.draw(label, states);
}

const sf::String& Orbiter::getLabel() const noexcept
{
	return label.getString();
}
const sf::String& Orbiter::getDescription() const noexcept
{
	return description;
}
