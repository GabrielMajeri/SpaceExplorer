#include "Common.hpp"
#include "StateManager/StateManager.hpp"
#include "StateManager/TitleScreenState.hpp"
#include "StateManager/MainMenuState.hpp"
#include "StateManager/PlayingState.hpp"

StateManager::StateManager(Context ctx) noexcept
	: mContext{ std::move(ctx) }
{
}

void StateManager::handleEvent(const sf::Event& e) noexcept
{
	for (auto& state : mStates)
		state->handleEvent(e);
}

void StateManager::update(const sf::Time& dt) noexcept
{
	for (auto& state : mStates)
		state->update(dt);

	applyPendingChanges();
}

void StateManager::render(sf::RenderTarget& tgt) const noexcept
{
	for (const auto& state : mStates)
		state->render(tgt);
}

void StateManager::pushState(GameState state) noexcept
{
	assert(mStates.empty() || mStates.back()->mType != state);

	mPending.push_back(PendingChange{ Action::Push, state }); 
}

void StateManager::popState() noexcept
{
	assert(!mStates.empty());
	
	mPending.push_back(PendingChange{ Action::Pop, GameState::None });
}

void StateManager::clear() noexcept
{
	assert(!mStates.empty());
	mPending.push_back(PendingChange{ Action::Clear, GameState::None });
}

bool StateManager::empty() const noexcept
{
	return mStates.empty();
}

auto StateManager::createState(GameState state) noexcept
{
	std::unique_ptr<IState> ptr = nullptr;
	switch (state) {
	case GameState::TitleScreen:
		ptr.reset(new TitleScreenState{ *this, mContext }); 
		break;
	case GameState::MainMenu:
		ptr.reset(new MainMenuState{ *this, mContext });
		break;
	case GameState::Playing:
		ptr.reset(new PlayingState{ *this, mContext });
		break;
	}
	return std::move(ptr);
}

void StateManager::applyPendingChanges() noexcept
{
	for (const auto& change : mPending) {
		switch (change.action) {
		case Action::Pop:
			mStates.pop_back();
			break;
		case Action::Push:
			mStates.push_back(createState(change.state));
			break;
		case Action::Clear:
			mStates.clear();
			break;
		}
	}
	mPending.clear();
}
