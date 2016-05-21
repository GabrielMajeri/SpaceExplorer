#pragma once

#include "State/StateManager.hpp"

class PausedState : public State
{
public:
	PausedState(StateManager& man);

	void handleEvent(const sf::Event& ev) override;
    void draw(sf::RenderTarget& tgt) const noexcept override;

private:
	sf::Text pauseText, infoText;

	void repositionGUI();
};
