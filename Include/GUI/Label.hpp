#pragma once
#include "Common.hpp"
#include "Component.hpp"

namespace GUI {
class Label final : public Component {
public:
	explicit Label(const sf::Font& font);

	bool isSelectable() const noexcept override;

	void setString(const std::string& text) noexcept;

	sf::Text& getText() noexcept;

	void handleEvent(const sf::Event& e) noexcept override { };
private:
	void draw(sf::RenderTarget& t, sf::RenderStates states) const noexcept override;

	sf::Text mText{};
};
}