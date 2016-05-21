#include "State/TitleScreen.hpp"

#include "Utility/Tools.hpp"

constexpr const char infoString[]
{
R"info(Apăsați tasta ENTER pentru a continua.
Apăsați tasta F11 pentru a întra în modul fullscreen.
Apăsați tasta ESCAPE pentru a ieși din program.
)info"
};

TitleScreen::TitleScreen(StateManager& man)
: State{ man }, field{ ctx }
{
	ctx.fonts.load("TitleScreenFont", ctx.om.getString("Font_Titlu"));

	titleText.setFont(ctx.fonts["TitleScreenFont"]);
	titleText.setString("Space Explorer");
	titleText.setFillColor(ctx.om.getColor("CuloareTextTitlu"));
	titleText.setCharacterSize(ctx.om.getUInt("MarimeTextTitlu"));

	infoText.setFont(ctx.fonts["Normal"]);
	infoText.setString(Utility::fromUTF8(infoString));
	infoText.setCharacterSize(ctx.om.getUInt("MarimeTextInformatii"));

	copyrightText.setFont(ctx.fonts["Bold"]);
	copyrightText.setString(Utility::fromUTF8("Licență GPL3 - Acest program este open source - © 2016 Majeri Gabriel"));
	copyrightText.setCharacterSize(ctx.om.getUInt("MarimeTextCopyright"));

	ctx.tex.load("MilkyWay", "Data/Textures/Galaxy/MilkyWaySide.png");
	galaxy.setTexture(ctx.tex["MilkyWay"]);

	ctx.tex.load("Earth", "Data/Textures/Local Cluster/Planets/Earth.png");
	ctx.tex["Earth"].setSmooth(true);
	earth.create(ctx.tex["Earth"], 160, sf::seconds(14));

	ctx.tex.load("Moon", "Data/Textures/Local Cluster/Planets/Moon.png");
	ctx.tex["Moon"].setSmooth(true);
	moon.create(ctx.tex["Moon"], 80, sf::seconds(8));

	repositionGUI();
}

TitleScreen::~TitleScreen()
{
	ctx.fonts.unload("TitleScreenFont");
	ctx.tex.clear();
}

void TitleScreen::handleEvent(const sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		if(e.key.code == sf::Keyboard::Return)
		{
			mgr.clear();
			mgr.add(StateManager::StateID::Running);
		}
		else if(e.key.code == sf::Keyboard::Escape)
			std::exit(0);
	}
	else if(e.type == sf::Event::Resized)
		repositionGUI();
}

void TitleScreen::update(const float dt)
{
	earth.update(dt);
	moon.update(dt);
}

void TitleScreen::draw(sf::RenderTarget& tgt) const noexcept
{
	tgt.draw(field);

	tgt.draw(galaxy);

	tgt.draw(earth);
	tgt.draw(moon);

	tgt.draw(titleText);
	tgt.draw(infoText);
	tgt.draw(copyrightText);
}

void TitleScreen::repositionGUI()
{
	titleText.setPosition(ctx.windowSize.x / 2, std::floor(ctx.windowSize.y / 3.5));
	Utility::centerText(titleText);
	infoText.setPosition(ctx.windowSize.x / 2, ctx.windowSize.y - ctx.windowSize.y / 4);
	Utility::centerText(infoText);
	copyrightText.setPosition(10, ctx.windowSize.y - copyrightText.getLocalBounds().height - 10);

	earth.setPosition(ctx.windowSize.x / 2, ctx.windowSize.y / 2);

	float esc = 1 - earth.getRadius() / (ctx.windowSize.y / 1.5);
	earth.setScale(esc, esc);

	earth.centerOrigin();

	moon.setPosition(earth.getPosition() - sf::Vector2f{ 250, 50 });

	float msc = esc / 4;
	moon.setScale(msc, msc);
	moon.centerOrigin();

	galaxy.setPosition(ctx.windowSize.x / 2 + 150, ctx.windowSize.y / 2 - 50);
	galaxy.setOrigin(galaxy.getLocalBounds().width / 2.f, galaxy.getLocalBounds().height / 2.f);
	galaxy.setRotation(-15);
	galaxy.setScale(2 * esc, 2 * esc);

	field.setSize(ctx.windowSize);
}
