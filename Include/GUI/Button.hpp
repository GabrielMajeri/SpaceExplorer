#pragma once
#include "Common.hpp"
#include "StateManager/Context.hpp"
#include "Component.hpp"

namespace GUI {
class Button : public Component {
public:
	using Callback = std::function<void()>;

	explicit Button(const sf::Texture& tex, const sf::IntRect& bounds,
		const sf::Font& font) noexcept;

	void setCallback(Callback c) noexcept;
	void setLabel(const std::string& string) noexcept;
	void setToggle(bool isToggle) noexcept;

	virtual bool isSelectable() const noexcept;
	virtual void setSelected(bool state) noexcept override;

	virtual void setActive(bool state) noexcept override;

	virtual void handleEvent(const sf::Event& e) noexcept override;
private:
	virtual void draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept override;

	enum TextureType { Normal, Selected, Pressed, TypeCount };
	void changeTexture(TextureType type) noexcept;

	sf::Sprite mButton;
	sf::Text mLabel;

	bool mIsToggle{ false };
	Callback mCallback{ };
};
}