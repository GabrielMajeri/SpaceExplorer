#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Keyboard.hpp>

class OptionsManager
{
public:
	/// Constructs a new options manager and loads options from file
	OptionsManager();

	/// Getters for different value types
	/// Gets a string
	const std::string& getString(const std::string& key) const;

	/// Gets a wide string
	sf::String getUTFString(const std::string& key) const;

	/// Gets an unsigned int
	uint32_t getUInt(const std::string& key) const;

	/// Gets an int
	int32_t getInt(const std::string& key) const;

	/// Gets a float
	float getFloat(const std::string& key) const;

	/// Gets a boolean
	bool getBool(const std::string& key) const;

	/// Gets a RGB color
	sf::Color getColor(const std::string& key) const;

	/// Gets a RGBA color
	sf::Color getColorA(const std::string& key) const;

	/// Gets a key binding
	sf::Keyboard::Key getKey(const std::string& key) const;

	/// DEBUG: prints all the key-value pairs
	void printAll() const noexcept;

private:
	/// Used to store the options
	std::unordered_map<std::string, std::string> options;
};
