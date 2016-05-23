#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Utility
{
	template <typename T>
	constexpr T PI = T(3.14159265359);

	/// Centers a text's origin
	void centerText(sf::Text& text);

	/// Converts an UTF-8 string to a sf::String
	sf::String fromUTF8(const std::string& str);

	float getRandomFloat();

	float getRandomFloat(float min, float max);

	constexpr float toRadians(float deg) { return deg * PI<float> / 180.f; }
	constexpr float toDegrees(float rad) { return rad * 180.f / PI<float>; }

	float abs(const sf::Vector2f& v);

	sf::Vector2f fromPolar(float d, float angl);
	std::pair<float, float> fromCartesian(const sf::Vector2f& vec);

	float clamp(float val, float mn, float mx);
}
