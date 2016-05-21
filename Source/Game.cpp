#include "Game.hpp"

Game::Game()
: ctx{ }, settings{ 0, 0, ctx.om.getUInt("AntiAliasing") },
 window{
  ctx.om.getBool("EcranComplet") ?
	sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode{ ctx.om.getUInt("LatimeFereastra"), ctx.om.getUInt("LungimeFereastra") },
  ctx.om.getUTFString("NumeFereastra"), ctx.om.getBool("EcranComplet") ? fullscreenStyle : windowedStyle
  },
   isFullscreen{ ctx.om.getBool("EcranComplet") },
   states{ ctx }
{
	ctx.windowSize = window.getSize();

	ctx.fonts.load("Normal", ctx.om.getString("Font_Normal"));
	ctx.fonts.load("Bold", ctx.om.getString("Font_Bold"));

	ctx.tex.load("Blank", "Data/Textures/Blank.png");
	ctx.tex["Blank"].setRepeated(true);

	setWindowOptions();
}

void Game::run()
{
	isRunning = true;
	isStandby = false;

	states.add(StateManager::StateID::TitleScreen);

	const sf::Time timePerFrame{ sf::seconds(ctx.om.getFloat("Fizica_DeltaTimp")) };
	const float deltaTime = timePerFrame.asSeconds();

	sf::Time elapsedTime{ sf::Time::Zero };
	sf::Clock frameClock;

	while(isRunning)
	{
		elapsedTime += frameClock.restart();

		handleEvents();

		while(elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;

			handleEvents();

			if(!isStandby)
			{
				update(deltaTime);
				states.updateGameState();
			}
		}

		draw();
	}
}

void Game::toggleFullscreen()
{
	isFullscreen = !isFullscreen;

	if(isFullscreen)
		window.create(sf::VideoMode::getFullscreenModes()[0],
						ctx.om.getUTFString("NumeFereastra"), fullscreenStyle);
	else
		window.create(sf::VideoMode{ ctx.om.getUInt("LatimeFereastra"), ctx.om.getUInt("LungimeFereastra") },
						ctx.om.getUTFString("NumeFereastra"), windowedStyle);

	setWindowOptions();
	ctx.windowSize = window.getSize();
}

void Game::setWindowOptions()
{
	window.setVerticalSyncEnabled(ctx.om.getBool("SincronizareVerticala"));

	window.setFramerateLimit(ctx.om.getUInt("LimitaFPS"));

	window.setMouseCursorVisible(!ctx.om.getBool("AscundeMouse"));
}

void Game::handleEvents()
{
	sf::Event e;
    while(window.pollEvent(e))
	{
		switch(e.type)
		{
		case sf::Event::Closed:
			isRunning = false;
			break;
		case sf::Event::KeyPressed:
			{
				if(e.key.code == static_cast<sf::Keyboard::Key>(ctx.om.getUInt("Tasta_EcranComplet")))
				{
					toggleFullscreen();

					// Create a fake resize event
					sf::Event rz;
					rz.type = sf::Event::Resized;
					rz.size.width = window.getSize().x;
					rz.size.height = window.getSize().y;

					// Pass the fake resize event to the state manager
					states.handleEvent(rz);
				}
			}
			break;

		default:
			break;
		}

		// Pass the event to the state manager
		states.handleEvent(e);
	}
}

void Game::update(const float dt)
{
	states.update(dt);
}

void Game::draw()
{
	window.clear(sf::Color::Black);

	states.draw(window);

	window.display();
}
