#pragma once

#include <SFML/Graphics.hpp>
#include "Utility/Context.hpp"

class Starfield final : public sf::Drawable
{
public:
	Starfield(Context& ctx);

	void setSize(const sf::Vector2u& sz);

	void setThreshold(float thr);

private:
	Context& ctx;

	float randSeed, threshold{ 0.985f };

	sf::Sprite cover;
	sf::Vector2u size;

	void draw(sf::RenderTarget& tgt, sf::RenderStates states) const noexcept override;
};
