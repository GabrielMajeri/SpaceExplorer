#include "Utility/OptionsManager.hpp"

#include "Utility/Parser.hpp"
#include "Utility/Tools.hpp"

#include <iostream>

OptionsManager::OptionsManager()
{
	// Open the file
	Parser parser{ "Data/Optiuni.txt" };

	std::string key, value;
	constexpr char separator = '=';

	// Read all options, skip comments
	while(parser.skipToNextLine())
	{
		parser.getNextKeyValuePair(key, value, separator);
		options.insert(std::make_pair(key, value));
	}
}

const std::string& OptionsManager::getString(const std::string& key) const
{
	return options.at(key);
}

sf::String OptionsManager::getUTFString(const std::string& key) const
{
    return sf::String::fromUtf8(std::begin(options.at(key)), std::end(options.at(key)));
}

uint32_t OptionsManager::getUInt(const std::string& key) const
{
	return std::stoul(options.at(key));
}

int32_t OptionsManager::getInt(const std::string& key) const
{
	return std::stol(options.at(key));
}

float OptionsManager::getFloat(const std::string& key) const
{
	return std::stof(options.at(key));
}

bool OptionsManager::getBool(const std::string& key) const
{
	return options.at(key) == "1";
}



sf::Color OptionsManager::getColor(const std::string& key) const
{
	const auto& value = options.at(key);
	uint32_t i = 0u;

	// Gets the next 8-bit unsigned integer value
	auto findNextInt = [&]() -> uint8_t
	{
		uint8_t result = 0u;

		while(!std::isdigit(value[i]))
			++i;

		while(std::isdigit(value[i]) && i < value.size())
			result = (result * 10u) + (value[i++] - '0');

		return result;
	};

	return sf::Color{ findNextInt(), findNextInt(), findNextInt() };
}

sf::Color OptionsManager::getColorA(const std::string& key) const
{
	const auto& value = options.at(key);
	uint32_t i = 0u;

	// Gets the next 8-bit unsigned integer value
	auto findNextInt = [&]() -> uint8_t
	{
		uint8_t result = 0u;

		while(!std::isdigit(value[i]))
			++i;

		while(std::isdigit(value[i]) && i < value.size())
			result = (result * 10u) + (value[i++] - '0');

		return result;
	};

	return sf::Color{ findNextInt(), findNextInt(), findNextInt(), findNextInt() };
}

sf::Keyboard::Key OptionsManager::getKey(const std::string& key) const
{
    return static_cast<sf::Keyboard::Key>(getInt(key));
}

void OptionsManager::printAll() const noexcept
{
	for(const auto& pair : options)
		std::cout << pair.first << '=' << pair.second << '\n';
}
