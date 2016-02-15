#pragma once
#include "Common.hpp"
#include "IState.hpp"

namespace GUI { class Label; }

/// This state represents the first state of the game. From here you can reach the
/// main menu.
class TitleScreenState final : public IState {
public:
	/// Constructs the title screen
	explicit TitleScreenState(StateManager& manager, Context& ctx) noexcept;
	~TitleScreenState();

	void handleEvent(const sf::Event& e) noexcept override;
	void update(const sf::Time& dt) noexcept override;
	void render(sf::RenderTarget& tgt) const noexcept override;

private:
	std::array<std::unique_ptr<GUI::Label>, 4> mText;
	sf::Sprite mBackground;

	/// Timer for the animation's keyframes
	unsigned int mAnimationTime{ 0u }, mMaxTime{ 300u };
	float mZoomSpeed{ 0.0007f };
};