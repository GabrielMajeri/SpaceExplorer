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

void Orbiter::update(const float dt)
{

}

void Orbiter::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
	states.transform *= getTransform();

	tgt.draw(sprite, states);
	tgt.draw(label, states);
}
