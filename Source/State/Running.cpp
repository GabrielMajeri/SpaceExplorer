#include "State/Running.hpp"

#include "State/StateManager.hpp"

RunningState::RunningState(StateManager& man)
: State{ man }, galaxy{ std::make_unique<Galaxy>(ctx, ctx.om.getString("Harta_Initiala")) }
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

	galaxy->handleEvent(e);
}

void RunningState::update(const float dt)
{
	galaxy->update(dt);
}

void RunningState::draw(sf::RenderTarget& tgt) const noexcept
{
	galaxy->draw(tgt);
}
