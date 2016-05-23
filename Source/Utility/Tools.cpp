#include "Utility/Tools.hpp"

#include <random>

namespace Utility
{
	void centerText(sf::Text& text)
	{
		text.setOrigin(std::floor(text.getLocalBounds().width / 2.f),  std::floor(text.getLocalBounds().height / 2.f));
	}

	sf::String fromUTF8(const std::string& str)
	{
        return sf::String::fromUtf8(std::begin(str), std::end(str));
	}

	static std::random_device rd;
	static std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 1);

	float getRandomFloat()
	{
		return dist(e2);
	}

	float getRandomFloat(float min, float max)
	{
		e2.seed(time(nullptr));
		std::uniform_real_distribution<> gen(min, max);
		return gen(e2);
	}

	float clamp(float val, float mn, float mx)
	{
		return std::max(mn, std::min(val, mx));
	}

	sf::Vector2f fromPolar(float d, float angl)
	{
        return { d * std::cos(angl), d * std::sin(angl) };
	}

	float abs(const sf::Vector2f& v)
	{
        return sqrt((v.x * v.x) + (v.y * v.y));
	}

	std::pair<float, float> fromCartesian(const sf::Vector2f& vec)
	{
		return std::pair<float, float>{ std::sqrt(vec.x * vec.x + vec.y * vec.y), std::atan2(vec.y, vec.x) };
	}
}
