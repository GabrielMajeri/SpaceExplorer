#pragma once
#include "Common.hpp"

namespace GUI {
/// A component is a part of the GUI system.
class Component : public sf::Drawable, public sf::Transformable,
	private NonCopyable
{
public:
	using ComponentPtr = std::shared_ptr<Component>;

	Component() = default;
	virtual ~Component() = default;

	virtual bool isSelectable() const noexcept = 0;

	bool isSelected() const noexcept;
	virtual void setSelected(bool value) noexcept;

	/// Checks whether this component is active or not
	virtual bool isActive() const noexcept;
	/// Sets whether the component is active or not
	virtual void setActive(bool value) noexcept;

	virtual void handleEvent(const sf::Event& e) noexcept = 0;

private:
	bool mIsSelected{ false }, mIsActive{ false };
};
}