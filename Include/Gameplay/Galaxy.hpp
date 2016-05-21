#pragma once

#include <string>

#include "Graphics/Starfield.hpp"

struct Context;

class Galaxy
{
public:
	Galaxy(Context& ctx, const std::string& filePath);

	bool inSystem() const noexcept;

	void handleEvent(const sf::Event& e);
	void update(const float dt);
	void draw(sf::RenderTarget& tgt) const noexcept;

private:
	Context& ctx;

	std::string name;
	std::string description;

	int32_t currentSystem{ -1 };
	float scale;

};
