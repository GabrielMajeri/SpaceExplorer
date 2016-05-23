#include "Gameplay/Orbiter.hpp"

#include "Utility/Tools.hpp"
#include "Utility/Context.hpp"

Orbiter::Orbiter(const Context& ctx, const sf::Texture& tex, const std::string& name)
: Entity(tex)
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

void Orbiter::setBodyToOrbit(const Orbiter* other) noexcept
{
	orbitBody = other;
}

void Orbiter::setOrbitOffset(const sf::Vector2f& off) noexcept
{
    this->off = off;
}

void Orbiter::setOrbitSpeed(const float spd) noexcept
{
    speed = spd;
}

void Orbiter::update(const float dt)
{
	if(orbitBody != nullptr)
	{
		currentPos += speed * dt;
		currentPos = Utility::clamp(currentPos, -360, 360);

        float x_cs = off.x + a * std::cos(currentPos);
        float y_cs = off.y + b * std::sin(currentPos);

        const auto& orbPos = orbitBody->getPosition();

        setPosition(orbPos.x - x_cs, orbPos.y - y_cs);
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
