#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Utility
{
	/// Centers a text's origin
	void centerText(sf::Text& text);

	/// Converts an UTF-8 string to a sf::String
	sf::String fromUTF8(const std::string& str);

	float getRandomFloat();

	float getRandomFloat(float min, float max);
}
