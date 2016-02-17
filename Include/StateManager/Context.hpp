#pragma once
#include "Common.hpp"
#include "Base/ResourceHandler.hpp"

class Game;
class Window;

struct Context {
	Context(Game& game) noexcept;
	
	Game& game;
	Window& window;
	
	TextureHandler& textures;
	FontHandler& fonts;
};