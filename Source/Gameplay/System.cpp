#include "Gameplay/System.hpp"

#include "Utility/Parser.hpp"


System::System(Context& ctx, const sf::View& view, const std::string& path)
: ctx{ ctx }, currentView{ view }
{
	Parser parser{ "Data/Maps/" + path };

	parser.skipToNextLine();
	float scale = parser.getNextFloat();

	parser.skipToNextLine();
	float w = parser.getNextFloat(), h = parser.getNextFloat();

	bounds = { 0, 0, w * scale, h * scale };

	setUpBorders();

    ctx.tex.load("Soare", "Data/Textures/Local Cluster/Stars/Sun.png");
    ctx.tex.load("Mercur", "Data/Textures/Local Cluster/Planets/Mercury.png");


	objects.emplace_back(ctx, ctx.tex["Soare"], "Soare");
	objects.back().setPosition(w / 2, h / 2);

	objects.emplace_back(ctx, ctx.tex["Mercur"], "Mercur");
	objects.back().setBodyToOrbit(&(*(objects.end() - 2)));
	objects.back().setParams(1000, 500);
	objects.back().setOrbitOffset({700, 0});
	objects.back().setOrbitSpeed(0.5);
}


void System::draw(sf::RenderTarget& tgt) const noexcept
{
	for(const auto& border : borders)
		tgt.draw(border);

	for(const auto& obj : objects)
		tgt.draw(obj);
}

const sf::FloatRect& System::getBounds() const noexcept
{
	return bounds;
}

void System::setUpBorders()
{
	sf::Vector2f sz(currentView.getSize());

	const float borderSize = ctx.om.getFloat("MarimeMargineSistem");

	auto& a = borders[0];
    a.setSize({sz.x / 2 + borderSize, bounds.height + 2 * (sz.y / 2 + borderSize)});
    a.setPosition(bounds.left - a.getSize().x + borderSize, bounds.top - (sz.y / 2 + borderSize));

    auto& b = borders[1];
    b.setSize({bounds.width + sz.x / 2, sz.y / 2 + borderSize});
    b.setPosition(borderSize + bounds.left, bounds.top - b.getSize().y);

    auto& c = borders[2];
    c.setSize({sz.x / 2 , bounds.height + 2 * (sz.y / 2) });
    c.setPosition(bounds.left + bounds.width - borderSize, bounds.top);

    auto& d = borders[3];
    d.setSize({c.getPosition().x - bounds.left - borderSize, sz.y / 2});
    d.setPosition(bounds.left + borderSize, bounds.top + bounds.height - borderSize);

	for(auto& border : borders)
		border.setFillColor(ctx.om.getColorA("CuloareMargineSistem"));
}

void System::update(const float dt)
{
    for(auto& obj : objects)
		obj.update(dt);
}

float System::getRadius() const noexcept
{
    return (bounds.left + bounds.width) / 2.f;
}

sf::Vector2f System::getCenter() const noexcept
{
	return { (bounds.left + bounds.width) / 2.f, (bounds.top + bounds.height) / 2.f };
}
