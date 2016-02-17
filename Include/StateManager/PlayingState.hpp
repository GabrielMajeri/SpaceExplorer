#pragma once
#include "Common.hpp"
#include "StateManager/IState.hpp"
#include "World/World.hpp"


class PlayingState final : public IState {
public:
	 PlayingState(StateManager& manager, Context& ctx) noexcept;
	~PlayingState();

	void handleEvent(const sf::Event& e) noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& t) const noexcept override;

private:
	World mWorld;
};