#include "Graphics/Window.h"

Window::Window(const unsigned int & width, const unsigned int & height,
	const std::string & title,
	const unsigned int & fpsTarget,
	const unsigned int & antialiasingLevel)
	: mWidth{ width }, mHeight{ height },
	mTitle{ title },
	mWindow{ sf::VideoMode{width, height}, title, sf::Style::Default, 
			sf::ContextSettings{0, 0, antialiasingLevel, 2, 0} },
	mFPSTarget{ fpsTarget },
	mTimePerFrame{ sf::seconds(1.f / mFPSTarget) },
	mLastFPS{ 0 }, mLastUPS{ 0 },
	mEventFunc{ nullptr }, mUpdateFunc{ nullptr }, mDrawFunc{ nullptr }
{
	
}

Window::~Window()
{
	stop();
}

void Window::start()
{
	if (mRunning == true)
		return;

	mRunning = true;
	mPaused = false;
	
	gameLoop();
}

void Window::gameLoop()
{
	sf::Event e;
	sf::Clock frameClock, fpsClock;
	sf::Time deltaTime = sf::Time::Zero;
	unsigned int frames = 0, updates = 0;

	while (mRunning == true) {
		deltaTime += frameClock.restart();

		while (deltaTime > mTimePerFrame) {
			deltaTime -= mTimePerFrame;

			while(mWindow.pollEvent(e))
				mEventFunc(e);

			if (mPaused == false) {
				mUpdateFunc(mTimePerFrame);
				++updates;
			}
		}

		mWindow.clear(sf::Color(0, 0, 0, 255));
		mDrawFunc(mWindow);
		mWindow.display();
		++frames;

		if (fpsClock.getElapsedTime().asMilliseconds() > 1000) {
			mLastFPS = frames;
			mLastUPS = updates;
			frames = 0;
			updates = 0; 
			fpsClock.restart();
		}
	}
}

void Window::stop()
{
	if (mRunning == false)
		return;

	mPaused = true;
	mRunning = false;
}

void Window::setVSync(const bool & val)
{
	mWindow.setVerticalSyncEnabled(val);
}

void Window::setEventHandleCallback(const EventFunc & func)
{
	mEventFunc = func;
}

void Window::setUpdateCallback(const UpdateFunc & func)
{
	mUpdateFunc = func;
}

void Window::setDrawCallback(const DrawFunc & func)
{
	mDrawFunc = func;
}

sf::RenderWindow & Window::getHandle()
{
	return mWindow;
}

const sf::RenderWindow & Window::getHandle() const
{
	return mWindow;
}

unsigned int & Window::getLastFPS()
{
	return mLastFPS;
}

unsigned int & Window::getLastUPS()
{
	return mLastUPS;
}

unsigned int & Window::getWidth()
{
	return mWidth;
}

unsigned int & Window::getHeight()
{
	return mHeight;
}
