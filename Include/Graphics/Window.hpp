#pragma once
#include "Common.hpp"
#include "StateManager/Context.hpp"

class Window final : private NonCopyable {
	friend class Game;
public:
	/// Constructs a new game
	explicit Window(Context& ctx) noexcept;

	/// Runs the main game loop
	void run() noexcept;

	/// Set the window's title
	void setTitle(const std::string& newTitle) noexcept;

	// Obtains the current view
	const sf::View& getView() const noexcept;

	const sf::Vector2u getSize() const noexcept;
private:
	/// Polls events, and then either handles them or calls the callback.
	void handleEvents() noexcept;
	/// Updates the statistics text and then calls the callback.
	void update() noexcept;
	/// Clears the screen, asks the game to render itself, then also renders debug
	/// information on the screen if it is enabled.
	void render() noexcept;

	/// Handles a resize of the window
	void handleResize(unsigned int width, unsigned int height);

	/// Toggles the window to and from windowed mode and fullscreen mode
	void toggleFullscreenMode() noexcept;
	/// Toggles standby mode, which reduces resource usage
	void toggleStandbyMode() noexcept;
				
	/// The size of the window.
	sf::VideoMode mWindowedSize{ 800u, 600u },
		/// The size of the fullscreen window. By default is set to a low
		/// resolution and then dynamically set to the highest possible
		/// display size.
		mFullscreenSize{ mWindowedSize };

	/// The window's title. Should be changed through the helper method
	/// to update the RenderWindow's title.
	std::string mTitle{ "Space Explorer" };

	/// The window style
	const sf::Uint32 cWindowedStyle{ sf::Style::Close }, cFullscreenStyle{ sf::Style::Fullscreen };

	/// The actual SFML window which we render to.
	sf::RenderWindow mWindow;

	/// This variable determines whether the game is windowed or fullscreen
	bool mIsFullscreen{ false },
		/// Running is a variable to determine whether the game is currently running
		/// or should close.
		mIsRunning{ false },
		/// This represents the state of standby mode, in which the game slows down
		/// and reduces its memory usage.
		mIsStandby{ false },
		/// Whether to display FPS/UPS or not
		mStatisticsDisplay{ !NDEBUG },
		/// Whether is vsync enabled or not
		mVSyncEnabled{ false };
	
	/// The framerate limit. If 0, then there is no FPS limit. Inaccurate.
	unsigned int mFPSLimit{ 0u };

	/// Callback functions:
	std::function<void(const sf::Event&) noexcept> mEventCallback;
	std::function<void(const sf::Time&) noexcept> mUpdateCallback;
	std::function<void(sf::RenderTarget&) noexcept> mRenderCallback;
	
	// Delta time for each frame
	const sf::Time cTimePerFrame{ sf::seconds(1.f / 60.f) };

	// Count how many updates happened in the last second
	size_t mUpdates{ 0u }, mFrames{ 0u };

	sf::Text mStatisticsText;
};