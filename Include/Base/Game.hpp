#pragma once
#include "Common.hpp"
#include "Graphics/Window.hpp"
#include "ResourceHandler.hpp"
#include "StateManager/StateManager.hpp"

/// This class represents an instance of the game itself
class Game final : private NonCopyable {
public:
	explicit Game() noexcept;
	void run() noexcept;

private:
	void handleEvent(const sf::Event& e) noexcept;
	void update(const sf::Time& dt) noexcept;
	void render(sf::RenderTarget& tgt) noexcept;

	/// The resource handlers
	TextureHandler mTextureHandler{};
	FontHandler mFontHandler{};

	/// The window that handles the game loop, FPS, UPS, resizing etc.
	Window mWindow;

	/// Context is able to access all it needs
	friend struct Context;

	/// The game state manager
	StateManager mStateManager;
};