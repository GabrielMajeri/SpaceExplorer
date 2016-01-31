#include "Player/KeyBindings.h"

KeyBinds::KeyBinds()
	: mKeys{ }
{
	setKeyBind(sf::Keyboard::W, "player_forward");
	setKeyBind(sf::Keyboard::A, "player_left");
	setKeyBind(sf::Keyboard::S, "player_backward");
	setKeyBind(sf::Keyboard::D, "player_right"); 
	setKeyBind(sf::Keyboard::Space, "player_shoot");
}

sf::Keyboard::Key KeyBinds::getKey(const std::string & command)
{
	return mCommands[command];
}

std::string KeyBinds::getCommand(const sf::Keyboard::Key & key)
{
	return mKeys[key];
}

void KeyBinds::setKeyBind(const sf::Keyboard::Key & key, const std::string & command)
{
	mKeys[key] = command;
	mCommands[command] = key;
}
