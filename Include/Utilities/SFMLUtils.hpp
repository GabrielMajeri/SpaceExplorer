#pragma once
#include <SFML/Graphics/Rect.hpp>

template <typename T>
bool contains(const sf::Rect<T>& a, const sf::Rect<T>& b)
{
	return a.left <= b.left && a.top <= b.top
		&& a.left + a.width >= b.left + b.width
		&& a.top + a.height >= b.top + b.width;
}

sf::FloatRect getBounds(const sf::View& view) noexcept;

bool isVisible(const sf::View& view, const sf::FloatRect& rect) noexcept;

void centerTextOrigin(sf::Text& text) noexcept;