#pragma once

#include "State/StateManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Graphics/AnimatedSphere.hpp"
#include "Graphics/Starfield.hpp"

class TitleScreen final : public State
{
public:
	TitleScreen(StateManager& man);
	~TitleScreen();

	void handleEvent(const sf::Event& e) override;
    void update(const float dt) override;
    void draw(sf::RenderTarget& tgt) const noexcept override;

private:
    sf::Text titleText, infoText, copyrightText;
    sf::Sprite galaxy;
	Starfield field;
	AnimatedSphere earth, moon;

	sf::Music music;

    void repositionGUI();
};
