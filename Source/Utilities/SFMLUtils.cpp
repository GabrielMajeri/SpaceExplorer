#include "Common.hpp"
#include "Utilities/SFMLUtils.hpp"

sf::FloatRect getBounds(const sf::View& view) noexcept
{
	return{ view.getCenter().x - view.getSize().x / 2.f,
		view.getCenter().y - view.getSize().y / 2.f,
		view.getSize().x,
		view.getSize().y };
}

bool isVisible(const sf::View& view, const sf::FloatRect& rect) noexcept
{
	auto bounds{ getBounds(view) };
	
	// Culling phase
	bounds.left -= 1.5f*rect.width;
	bounds.top -= 1.5f*rect.height;
	bounds.width += 3.f*rect.width;
	bounds.height += 3.f*rect.height;

	return contains(bounds, rect);
}

void centerTextOrigin(sf::Text& text) noexcept
{
	auto b{ text.getLocalBounds() };

	text.setOrigin(std::floorf(b.left + b.width / 2.f), std::floorf(b.top + b.height / 2.f));
}
