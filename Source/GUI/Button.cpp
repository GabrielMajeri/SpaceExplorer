#include "Common.hpp"
#include "GUI/Button.hpp"

GUI::Button::Button(const sf::Texture& tex, const sf::IntRect& bounds,
	const sf::Font& font) noexcept
	: mButton{ tex, bounds }
{
	mLabel.setCharacterSize(18);
	mLabel.setFont(font);
	changeTexture(Normal);

	const auto& b{ mButton.getTextureRect() };
	setOrigin(b.width / 2.f, b.height / 2.f);
	mLabel.setPosition(b.width / 2.f, b.height / 2.f); 
	centerTextOrigin(mLabel);
}

void GUI::Button::setCallback(Callback c) noexcept
{
	mCallback = std::move(c);
}

void GUI::Button::setLabel(const std::string& string) noexcept
{
	mLabel.setString(string);
	const auto& b{ mButton.getTextureRect() };
	mLabel.setPosition(b.width / 2.f, b.height / 2.f);
	centerTextOrigin(mLabel);
}

void GUI::Button::setToggle(bool isToggle) noexcept
{
	mIsToggle = isToggle;
}

bool GUI::Button::isSelectable() const noexcept
{
	return true;
}

void GUI::Button::setSelected(bool state) noexcept
{
	Component::setSelected(state);
	if (state)
		changeTexture(Selected);
	else
		changeTexture(Normal);
}

void GUI::Button::changeTexture(TextureType type) noexcept
{
	const auto& bounds{ mButton.getTexture()->getSize() };
	auto height{ bounds.y / TypeCount };

	mButton.setTextureRect({ 0, static_cast<int>(type * height), 
		static_cast<int>(bounds.x), static_cast<int>(height) });
}

void GUI::Button::setActive(bool state) noexcept
{
	Component::setActive(state);
	if (state) {
		if (mIsToggle)
			changeTexture(Pressed);

		if (mCallback)
			mCallback();

		if (!mIsToggle)
			setActive(false);
	}
	else {
		if (isSelected())
			changeTexture(Selected);
		else
			changeTexture(Normal);
	}
}

void GUI::Button::handleEvent(const sf::Event& e) noexcept
{
	
}

void GUI::Button::draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept
{
	states.transform.combine(getTransform());

	t.draw(mButton, states);
	t.draw(mLabel, states);
}