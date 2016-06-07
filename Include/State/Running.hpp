#pragma once

#include "State/State.hpp"

#include "Gameplay/Galaxy.hpp"

#include <SFML/Audio/Music.hpp>

class StateManager;

class RunningState final : public State
{
public:
	RunningState(StateManager& man);
	~RunningState();

	void run();

	void handleEvent(const sf::Event& e) override;
    void update(const float dt) override;
    void draw(sf::RenderTarget& tgt) const noexcept override;

private:
	std::unique_ptr<Galaxy> galaxy;

	sf::Music bgm;
};
