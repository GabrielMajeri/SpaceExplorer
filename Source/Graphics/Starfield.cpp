#include "Graphics/Starfield.hpp"

#include "Utility/Tools.hpp"

Starfield::Starfield(Context& ctx)
: ctx{ ctx }, randSeed{ Utility::getRandomFloat(10, 1000) }
{
	cover.setTexture(ctx.tex["Blank"]);
	setSize(ctx.windowSize);

	ctx.shaders.load("StarfieldShader", "Data/Shaders/Starfield.frag", sf::Shader::Fragment);
}

void Starfield::setSize(const sf::Vector2u& sz)
{
	size = sz;
	cover.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Starfield::setThreshold(float thr)
{
	threshold = thr;
}

void Starfield::draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept
{
    sf::View tmp = tgt.getView();

    tgt.setView(tgt.getDefaultView());

    ctx.shaders["StarfieldShader"].setUniform("starThreshold", threshold);
    ctx.shaders["StarfieldShader"].setUniform("numSeed", randSeed);

    states.shader = &ctx.shaders["StarfieldShader"];
	tgt.draw(cover, states);

    tgt.setView(tmp);
}
