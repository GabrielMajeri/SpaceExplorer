#include "Common.hpp"
#include "GUI/Label.hpp"

GUI::Label::Label(const sf::Font& font)
{
	mText.setFont(font);
}

bool GUI::Label::isSelectable() const noexcept
{
	return false;
}

void GUI::Label::setString(const std::string& text) noexcept
{
	mText.setString(text);
	centerTextOrigin(mText);
}

sf::Text& GUI::Label::getText() noexcept
{
	return mText;
}

void GUI::Label::draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept
{
	states.transform.combine(getTransform());

	t.draw(mText, states);
}