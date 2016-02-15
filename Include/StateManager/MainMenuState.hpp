#pragma once
#include "Common.hpp"
#include "IState.hpp"
#include "GUI/Container.hpp"

class MainMenuState final : public IState {
public:
	explicit MainMenuState(StateManager& manager, Context& ctx) noexcept;
	~MainMenuState();

	void handleEvent(const sf::Event& e) noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& tgt) const noexcept override;

private:
	GUI::Container mRootPane{};
	sf::Sprite mBackground;
};