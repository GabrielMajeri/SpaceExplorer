#pragma once
#include "Common.hpp"
#include "Base/ResourceHandler.hpp"

class Game;
class Window;

struct Context {
	explicit Context(Game& game) noexcept;
	
	Game& game;
	Window& window;
	
	TextureHandler& textures;
	FontHandler& fonts;
};