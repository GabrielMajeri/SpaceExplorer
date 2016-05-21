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
}
