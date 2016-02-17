#include "Common.hpp"
#include "Utilities/MetadataParser.h"

namespace Metadata {
	TextureMeta loadTextureMeta(const std::string& path) noexcept
	{
		std::ifstream in{ path };
		std::string id;

		unsigned int np = 0;
		std::vector<sf::IntRect> parts;
		
		in >> np;

		in >> id;

		parts.reserve(np);

		for (unsigned int i = 0; i < np; ++i) {
			int x, y, width, height;
			in >> x >> y >> width >> height;
			parts.emplace_back(x, y, width, height);
		}



		return{ np, id, parts };
	}
}
