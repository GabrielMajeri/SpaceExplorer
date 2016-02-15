#include "Common.hpp"
#include "GUI/Component.hpp"

bool GUI::Component::isSelected() const noexcept
{
	return mIsSelected;
}

void GUI::Component::setSelected(bool value) noexcept
{
	mIsSelected = std::move(value);
}

bool GUI::Component::isActive() const noexcept
{
	return mIsActive;
}

void GUI::Component::setActive(bool value) noexcept
{
	mIsActive = std::move(value);
}
