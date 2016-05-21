#include "Gameplay/System.hpp"

#include "Utility/Parser.hpp"

System::System(Context& ctx, const std::string& path)
: ctx{ ctx }
{
	Parser parser{ "Data/Maps/" + path };

	parser.skipToNextLine();
	float scale = parser.getNextFloat();

	parser.skipToNextLine();
	float w = parser.getNextFloat(), h = parser.getNextFloat();
}


void System::draw(sf::RenderTarget& tgt) const noexcept
{
	for(const auto& obj : objects)
		tgt.draw(obj);
}

const sf::FloatRect& System::getBounds() const noexcept
{
	return bounds;
}
