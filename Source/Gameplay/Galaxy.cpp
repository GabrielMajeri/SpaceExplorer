#include "Gameplay/Galaxy.hpp"

#include "Utility/Parser.hpp"
#include "Utility/Context.hpp"

#include "Utility/Tools.hpp"


Galaxy::SystemView::SystemView(Context& ctx, sf::Texture& tex, const std::string& label, uint32_t pos)
: view{ ctx, tex, label }, assocSystem{ pos }
{
	view.setOrigin(view.getLocalBounds().width / 2, view.getLocalBounds().height / 2);
}

Galaxy::Galaxy(Context& ctx, const std::string& filePath)
: ctx{ ctx }, backgroundStars{ ctx }
{
	Parser parser("Data/Maps/" + filePath);

	parser.getNextString(name);
	parser.getNextString(description);

	parser.skipToNextLine();
	scale = parser.getNextFloat();

	parser.skipToNextLine();
	float w = scale * parser.getNextFloat(), h = scale * parser.getNextFloat();
	bounds = {-w / 2, -h / 2, w, h};

	parser.skipToNextLine();
	currentSystem = parser.getNextInt();

	while(parser.skipToNextLine())
	{
		float dist = parser.getNextFloat();
		float rad = Utility::toRadians(parser.getNextFloat());

		std::string name;
		parser.getNextString(name);

		std::string path;
		parser.getNextString(path);

		if(path != ".")
			systems.emplace_back(ctx, path);

		std::string texName, texPath;
		parser.getNextString(texName);
		parser.getNextString(texPath);

		ctx.tex.load(texName, "Data/Textures/" + texPath);

		systemViews.emplace_back(ctx, ctx.tex[texName], name, (path != "." ? systems.size() - 1 : -1));
		systemViews.back().view.setPosition(scale * Utility::fromPolar(dist, rad));
	}

	ctx.tex.load("SpaceshipTexture", "Data/Textures/Spaceship.png");
	ctx.tex["SpaceshipTexture"].setSmooth(true);
	spaceship = std::make_unique<Spaceship>(ctx, ctx.tex["SpaceshipTexture"]);

	recalculateView();
}

bool Galaxy::inSystem() const noexcept
{
	return currentSystem >= 0;
}

void Galaxy::handleEvent(const sf::Event& e)
{
	if(e.type == sf::Event::Resized)
	{
		backgroundStars.setSize(ctx.windowSize);
		recalculateView();
	}
	else if(e.type == sf::Event::KeyPressed)
	{
        if(e.key.code == ctx.om.getKey("Tasta_ZoomIn"))
		{
			if(viewZoom > 1)
				viewZoom -= 1;
		}
		else if(e.key.code == ctx.om.getKey("Tasta_ZoomOut"))
		{
			if(viewZoom < 10)
				viewZoom += 1;
		}
		recalculateView();
	}
}

void Galaxy::update(const float dt)
{
	spaceship->update(dt);
	currentView.setCenter(spaceship->getPosition());

	if(spaceship->getPosition().x < bounds.left || spaceship->getPosition().y < bounds.top
		|| spaceship->getPosition().x > bounds.left + bounds.width || spaceship->getPosition().y > bounds.top + bounds.height)
		spaceship->stop();
}

void Galaxy::draw(sf::RenderTarget& tgt) const noexcept
{
	tgt.setView(currentView);

	// First draw the background starfield
	tgt.draw(backgroundStars);

	// Draw the planets / stars
	if(inSystem())
	{
		systems[currentSystem].draw(tgt);
	}
	else
	{
		for(const auto& systemView : systemViews)
			tgt.draw(systemView.view);

        for(const auto& border : borders)
			tgt.draw(border);
	}

	// Finally draw the spaceship
	tgt.draw(*spaceship);

	tgt.setView(tgt.getDefaultView());
}

void Galaxy::recalculateView()
{
	currentView.setSize(ctx.windowSize.x * viewZoom, ctx.windowSize.y * viewZoom);

	setUpBorders();
}

void Galaxy::setUpBorders()
{
	sf::Vector2f sz(currentView.getSize());

	constexpr auto padding = 30.f;

	auto& a = borders[0];
    a.setSize({sz.x / 2 + padding, bounds.height + 2 * (sz.y / 2 + padding)});
    a.setPosition(bounds.left - a.getSize().x, bounds.top - (sz.y / 2 + padding));

    auto& b = borders[1];
    b.setSize({bounds.width + sz.x / 2 + padding, sz.y / 2 + padding});
    b.setPosition(bounds.left, bounds.top - b.getSize().y);

    auto& c = borders[2];
    c.setSize({sz.x / 2 + padding, bounds.height + 2 * (sz.y / 2 + padding) });
    c.setPosition(bounds.left + bounds.width, bounds.top);

    auto& d = borders[3];
    d.setSize({c.getPosition().x - bounds.left, sz.y / 2 + padding});
    d.setPosition(bounds.left, bounds.top + bounds.height);

    for(auto& border : borders)
		border.setFillColor({0, 40, 150, 100});
}
