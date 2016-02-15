#include "Common.hpp"
#include "StateManager/MainMenuState.hpp"
#include "StateManager/Context.hpp"
#include "GUI/Button.hpp"
#include "Graphics/Window.hpp"
#include "StateManager/StateManager.hpp"

MainMenuState::MainMenuState(StateManager& manager, Context& ctx) noexcept
	: IState{ manager, ctx }
{
	mContext.textures.tryLoad("StartButton", "Resources/Textures/GUI/ButtonMainMenu.png");
	mContext.fonts.tryLoad("Montserrat", "Resources/Fonts/Montserrat.ttf");

	auto startButton = std::make_shared<GUI::Button>(
		mContext.textures.get("StartButton"), sf::IntRect{ 0, 0, 100, 100 },
		mContext.fonts.get("Montserrat"));

	startButton->setLabel("Start Game");
	startButton->setPosition(0, 0);
	startButton->setCallback([&]() -> void { 
		mManager.popState(); 
		mManager.pushState(GameState::Playing);
	});

	mRootPane.addChild(std::move(startButton));

	auto optionsButton = std::make_shared<GUI::Button>(
		mContext.textures.get("StartButton"), sf::IntRect{ 0, 0, 100, 100 },
		mContext.fonts.get("Montserrat"));

	optionsButton->setLabel("Options");
	optionsButton->setPosition(0, 75);

	mRootPane.addChild(std::move(optionsButton));

	auto exitButton = std::make_shared<GUI::Button>(
		mContext.textures.get("StartButton"), sf::IntRect{ 0, 0, 100, 100 },
		mContext.fonts.get("Montserrat"));

	exitButton->setLabel("Exit");
	exitButton->setPosition(0, 150);
	exitButton->setCallback([&]() -> void { mManager.clear(); });

	mRootPane.addChild(std::move(exitButton));

	auto sz = sf::Vector2u{ mContext.window.getSize() };
	mRootPane.setPosition(sz.x / 2.f, sz.y / 2.f - 100);

	mContext.textures.tryLoad("Stars1", "Resources/Textures/Background/Stars.png");
	mContext.textures.get("Stars1").setRepeated(true);
	mBackground.setTexture(mContext.textures.get("Stars1"));
	mBackground.setTextureRect({ 0, 0, 10000, 10000 });
}

MainMenuState::~MainMenuState()
{
	mContext.textures.tryUnload("Button");
}

void MainMenuState::handleEvent(const sf::Event& e) noexcept
{
	mRootPane.handleEvent(e);

	if (e.type == sf::Event::Resized) {
		auto sz = sf::Vector2u{ e.size.width, e.size.height };
		mRootPane.setPosition(sz.x / 2.f, sz.y / 2.f - 100);
	}
}

void MainMenuState::update(const sf::Time& dt) noexcept
{
	
}

void MainMenuState::render(sf::RenderTarget& tgt) const noexcept
{
	tgt.draw(mBackground);
	tgt.draw(mRootPane);
}