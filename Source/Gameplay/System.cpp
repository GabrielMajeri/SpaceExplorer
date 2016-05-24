#include "Gameplay/System.hpp"

#include "Utility/Parser.hpp"
#include "Utility/Tools.hpp"

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

	while(parser.skipToNextLine())
	{
		std::string label;
		parser.getNextString(label);

		std::string texId, texPath;
		parser.skipToNextLine();
		parser.getNextString(texId);

		parser.skipToNextLine();
		parser.getNextString(texPath);

		ctx.tex.load(texId, "Data/Textures/" + texPath);

		parser.skipToNextLine();
		int32_t isFixed = parser.getNextInt();

		parser.skipToNextLine();
		if(isFixed)
		{
			float dist = parser.getNextFloat() * scale, rot = parser.getNextFloat() * scale;

			objects.emplace_back(std::make_unique<Orbiter>(ctx, ctx.tex[texId], label));

			auto pos = Utility::fromPolar(dist, rot);
			objects.back()->setPosition(pos.x + bounds.width / 2, pos.y + bounds.height / 2);
		}
		else
		{
			float apoapsis = parser.getNextFloat() * scale, periapsis = parser.getNextFloat() * scale;

			parser.skipToNextLine();
			float spd = parser.getNextFloat();

            parser.skipToNextLine();
			uint32_t orbitedID = parser.getNextInt();

			parser.skipToNextLine();
			float rot = parser.getNextFloat();

			objects.emplace_back(std::make_unique<Orbiter>(ctx, ctx.tex[texId], label));
			objects.back()->setBodyToOrbit(objects[orbitedID].get());
			objects.back()->setParams(apoapsis, periapsis);
			objects.back()->setOrbitRotation(Utility::toRadians(rot));
			objects.back()->setOrbitSpeed(spd);
		}

	}
}


void System::draw(sf::RenderTarget& tgt) const noexcept
{
	for(const auto& border : borders)
		tgt.draw(border);

	for(const auto& obj : objects)
		tgt.draw(*obj);
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
		obj->update(dt);
}

float System::getRadius() const noexcept
{
    return (bounds.left + bounds.width) / 2.f;
}

sf::Vector2f System::getCenter() const noexcept
{
	return { (bounds.left + bounds.width) / 2.f, (bounds.top + bounds.height) / 2.f };
}
