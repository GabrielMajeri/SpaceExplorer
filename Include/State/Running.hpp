#pragma once

#include "State/State.hpp"

#include "Gameplay/Galaxy.hpp"

class StateManager;

class RunningState final : public State
{
public:
	RunningState(StateManager& man);

	void run();

	void handleEvent(const sf::Event& e) override;
    void update(const float dt) override;
    void draw(sf::RenderTarget& tgt) const noexcept override;

private:
	std::unique_ptr<Galaxy> galaxy;
};
