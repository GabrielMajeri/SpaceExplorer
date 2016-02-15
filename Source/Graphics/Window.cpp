#include "Common.hpp"
#include "Graphics/Window.hpp"

Window::Window(Context& ctx) noexcept
	: mWindow{ mWindowedSize, mTitle, cWindowedStyle }
{
	// The window must open for the game to continue.
	assert(mWindow.isOpen());

	// Get the fullscreen size dynamically.
	mFullscreenSize = *std::cbegin(sf::VideoMode::getFullscreenModes());

	// If there is a framerate limit, then enable it
	mWindow.setFramerateLimit(mFPSLimit);
	
	// Initialize the statistics font and text
	ctx.fonts.tryLoad("Arial", "Resources/Fonts/Arial.ttf");

	mStatisticsText.setFont(ctx.fonts.get("Arial"));
	mStatisticsText.setCharacterSize(18);
	mStatisticsText.setString("UPS: 0\nFPS: 0");
}

void Window::run() noexcept
{
	// The game loop should not be already running
	assert(!mIsRunning);

	// The callbacks should have been set up already
	assert(mEventCallback && mUpdateCallback && mRenderCallback);

	mIsRunning = true;

	sf::Time elapsedTime{ sf::Time::Zero };
	sf::Clock frameClock, statsClock;

	// The main game loop. The game closes when it stops running.
	while (mIsRunning) {
		// First poll all events that happened after the last render
		handleEvents();

		// Determine how much time we spent between frames (the delta time)
		elapsedTime += frameClock.restart();

		// Integrate the game state again and again until we have only one frame
		// to catch up to.
		while (elapsedTime > cTimePerFrame) {
			// Another update passed
			elapsedTime -= cTimePerFrame;

			// Handle any events that happened in the last update loop
			handleEvents();

			// If we are not in standby mode
			if (!mIsStandby) 
				// Update the game state
				update();
		}
		
		// Render to screen
		render();

		// If need be, update the statistics
		if (statsClock.getElapsedTime().asSeconds() > 1.f) {
			mStatisticsText.setString("UPS: " + std::to_string(mUpdates)
									+ "\nFPS: " + std::to_string(mFrames));

			mUpdates = mFrames = 0;
			statsClock.restart();
		}
	}
}

void Window::setTitle(const std::string & newTitle) noexcept
{
	// First update the title variable
	mTitle.assign(newTitle);

	// Then change the window's actual title
	mWindow.setTitle(mTitle);
}

const sf::View & Window::getView() const noexcept
{
	return mWindow.getView();
}

const sf::Vector2u Window::getSize() const noexcept
{
	return mWindow.getSize();
}

void Window::handleEvents() noexcept
{
	// We only use SFML's event, no confusion here
	using sf::Event;
	// A temporary variable to hold the events as they are taken from the queue
	Event e;
	// Go through all the events on the queue
	while (mWindow.pollEvent(e)) {
		switch (e.type) {
		case Event::KeyPressed:
			mEventCallback(e);
			break;
		case Event::KeyReleased: 
			if (e.key.code == sf::Keyboard::F11) {
				toggleFullscreenMode();
				Event resize;
				resize.type = sf::Event::Resized;
				resize.size.width = getSize().x;
				resize.size.height = getSize().y;
				mEventCallback(resize);
				break;
			}
			mEventCallback(e);
			break;
		case Event::LostFocus:
			// Enter standby mode, reducing resource usage
			toggleStandbyMode();
			break;
		case Event::GainedFocus:
			// Exit standby mode
			toggleStandbyMode();
			break;
		case Event::Closed:
			mIsRunning = false;
			// We should return, no point in polling other events
			return;
		case Event::Resized:
			handleResize(e.size.width, e.size.height);
			mEventCallback(e);
			break;
		default:
			// Have the callback handle other events
			mEventCallback(e);
			return;
		}
	}
}

void Window::update() noexcept
{
	mUpdateCallback(cTimePerFrame);
	++mUpdates;
}

void Window::render() noexcept
{
	/// First clear the previous buffer
	mWindow.clear(sf::Color::Black);

	/// Calls the renderer callback
	mRenderCallback(static_cast<sf::RenderTarget&>(mWindow));

	/// If statistics are enabled
	if (mStatisticsDisplay) {
		/// Reset the view
		mWindow.setView(mWindow.getDefaultView());
		/// Draw statistics to screen
		mWindow.draw(mStatisticsText);
	}

	/// Flip the buffer to the screen
	mWindow.display();

	/// Increase the frame counter
	++mFrames;
}

void Window::handleResize(unsigned int width, unsigned int height)
{
	// Create a new temp holding variable
	auto oldView{ mWindow.getView() };
	// Set the temp variable's size
	oldView.setSize(static_cast<float>(width), static_cast<float>(height));
	// Change the viewport's size
	mWindow.setView(oldView); 
	
	// Change the window's size
	mWindow.setSize(sf::Vector2u{ width, height });
}

void Window::toggleFullscreenMode() noexcept
{
	// Toggle fullscreen mode
	mIsFullscreen = !mIsFullscreen;

	/// Enter fullscreen mode
	if (mIsFullscreen)
		mWindow.create(mFullscreenSize, mTitle, cFullscreenStyle);
	/// Enter windowed mode
	else 
		mWindow.create(mWindowedSize, mTitle, cWindowedStyle);
	
	/// Inform the window and view it's been resized
	handleResize(mWindow.getSize().x, mWindow.getSize().y);
}

void Window::toggleStandbyMode() noexcept
{
	// Toggle mIsStandby to limit UPS to 0.
	mIsStandby = !mIsStandby;

	if (mIsStandby)
		// Limit FPS to 10 to reduce GPU usage.
		mWindow.setFramerateLimit(10u);
	else
		// Set the FPS limit
		mWindow.setFramerateLimit(mFPSLimit);
}
