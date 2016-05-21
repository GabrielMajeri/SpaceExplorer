#include "State/State.hpp"
#include "State/StateManager.hpp"

State::State(StateManager& man) noexcept
: mgr{ man }, ctx{ man.ctx }
{
}

void State::handleEvent(const sf::Event&)
{

}

void State::update(const float)
{

}

void State::draw(sf::RenderTarget&) const noexcept
{

}
