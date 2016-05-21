#include "Gameplay/System.hpp"

#include "Utility/Parser.hpp"

System::System(Context& ctx, const std::string& path)
: ctx{ ctx }
{
	Parser parser{ "Data/Maps/" + path };
}


void System::draw(sf::RenderTarget& tgt) const noexcept
{
	for(const auto& obj : objects)
		tgt.draw(obj);
}
