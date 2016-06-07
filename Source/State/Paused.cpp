#include "State/Paused.hpp"

#include "Utility/Tools.hpp"

PausedState::PausedState(StateManager& man)
: State{ man }
{
	pauseText.setFont(ctx.fonts["Bold"]);
	pauseText.setString(Utility::fromUTF8("Pauză"));
	pauseText.setCharacterSize(80);

	infoText.setFont(ctx.fonts["Normal"]);
	infoText.setString(Utility::fromUTF8("Apăsați ESCAPE pentru a ieși, sau ENTER pentru a reveni."));

	repositionGUI();
}

void PausedState::handleEvent(const sf::Event& e)
{
	if(e.type == sf::Event::KeyPressed)
	{
		if(e.key.code == sf::Keyboard::Escape)
		{
			mgr.clear();
		}
		else if(e.key.code == sf::Keyboard::Return)
			mgr.pop();
	}
	else if(e.type == sf::Event::Resized)
		repositionGUI();
}

void PausedState::draw(sf::RenderTarget& tgt) const noexcept
{
	tgt.draw(pauseText);
	tgt.draw(infoText);
}

void PausedState::repositionGUI()
{
	Utility::centerText(pauseText);
	Utility::centerText(infoText);

	pauseText.setPosition(ctx.windowSize.x / 2.f, ctx.windowSize.y / 2.5f);
    infoText.setPosition(ctx.windowSize.x / 2.f, ctx.windowSize.y - ctx.windowSize.y / 2.5f);
}
