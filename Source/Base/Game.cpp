#include "Common.hpp"
#include "Base/Game.hpp"

Game::Game() noexcept
	: mWindow { Context{ *this } }, mStateManager{ Context{ *this } }
{
	// Set up the callbacks
	mWindow.mEventCallback = std::move([this](const sf::Event& e) noexcept -> void { handleEvent(e); });
	mWindow.mUpdateCallback = std::move([this](const sf::Time& dt) noexcept -> void { update(dt); });
	mWindow.mRenderCallback = std::move([this](sf::RenderTarget& t) noexcept -> void { render(t); });
}

void Game::run() noexcept
{
	// Push the title screen to the stack
	mStateManager.pushState(GameState::TitleScreen);

	// Allow the manager to apply the pending changes
	mStateManager.update(sf::Time::Zero);

	// Run the main game loop
	mWindow.run();
}

void Game::handleEvent(const sf::Event& e) noexcept
{
	mStateManager.handleEvent(e);
}

void Game::update(const sf::Time& dt) noexcept
{
	mStateManager.update(dt);
	if (mStateManager.empty())
		mWindow.mIsRunning = false;
}

void Game::render(sf::RenderTarget& tgt) noexcept
{
	mStateManager.render(tgt);
}
