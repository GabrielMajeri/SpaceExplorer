#pragma once
#include "Global.h"

class KeyBinds {
public:
	KeyBinds();

	sf::Keyboard::Key getKey(const std::string & command);
	std::string getCommand(const sf::Keyboard::Key & key);

	void setKeyBind(const sf::Keyboard::Key & key, const std::string & command);
private:
	std::map<sf::Keyboard::Key, std::string> mKeys;
	std::map<std::string, sf::Keyboard::Key> mCommands;
};