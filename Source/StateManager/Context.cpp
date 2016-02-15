#include "Common.hpp"
#include "StateManager/Context.hpp"
#include "Base/Game.hpp"

Context::Context(Game& game) noexcept
	: game{ game }, window{ game.mWindow },
	textures{ game.mTextureHandler }, fonts { game.mFontHandler }
{ }