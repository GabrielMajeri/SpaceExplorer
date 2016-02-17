#include "Common.hpp"
#include "StateManager/PlayingState.hpp"
#include "StateManager/Context.hpp"
#include "EntitySystem/Component.hpp"
#include "EntitySystem/Components/CTransformable.hpp"
#include "EntitySystem/Components/CSprite.hpp"
#include "EntitySystem/Components/CPlayerControl.hpp"

PlayingState::PlayingState(StateManager & manager, Context & ctx) noexcept
	: IState{ manager, ctx }, mWorld{ "demoworld.txt", ctx }
{
}

PlayingState::~PlayingState()
{
	
}

void PlayingState::handleEvent(const sf::Event& e) noexcept
{
	mWorld.handleEvent(e);
}

void PlayingState::update(const sf::Time& dt) noexcept
{
	mWorld.update(dt);
}

void PlayingState::render(sf::RenderTarget& t) const noexcept
{
	mWorld.render(t);
}