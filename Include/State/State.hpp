#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Context;
class StateManager;

class State
{
public:
	virtual void handleEvent(const sf::Event& ev);
    virtual void update(const float dt);
	virtual void draw(sf::RenderTarget& tgt) const noexcept;

	virtual ~State() = default;

protected:
	State(StateManager& stateManager) noexcept;

	StateManager& mgr;
	Context& ctx;
};
