#include "State/Running.hpp"

#include "State/StateManager.hpp"

RunningState::RunningState(StateManager& man)
: State{ man }, galaxy{ ctx, ctx.om.getString("Harta_Initiala") }
{

}

void RunningState::handleEvent(const sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed)
	{
        if(e.key.code == sf::Keyboard::Escape)
		{
            mgr.add(StateManager::StateID::Paused);
		}
	}
}

void RunningState::update(const float dt)
{

}

void RunningState::draw(sf::RenderTarget& tgt) const noexcept
{

}
