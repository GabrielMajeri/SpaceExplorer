#pragma once
#include "Common.hpp"

namespace Metadata {
	struct TextureMeta {
		const unsigned int numParts;
		const std::string id;
		
		std::vector<sf::IntRect> parts;
	};
	
	TextureMeta loadTextureMeta(const std::string& path) noexcept;
}