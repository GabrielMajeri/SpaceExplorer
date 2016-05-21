#include "Gameplay/Galaxy.hpp"

#include "Utility/Parser.hpp"
#include "Utility/Context.hpp"

Galaxy::Galaxy(Context& ctx, const std::string& filePath)
: ctx{ ctx }
{
	Parser parser("Data/Maps/" + filePath);

	parser.getNextString(name);
	parser.getNextString(description);
}

bool Galaxy::inSystem() const noexcept
{
	return currentSystem >= 0;
}

void Galaxy::handleEvent(const sf::Event& e)
{
	if(e.type == sf::Event::Resized)
	{

	}
}

void Galaxy::update(const float dt)
{

}

void Galaxy::draw(sf::RenderTarget& tgt) const noexcept
{

}
