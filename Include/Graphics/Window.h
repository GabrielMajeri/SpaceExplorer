#pragma once
#include "Global.h"

using EventFunc = std::function<void(const sf::Event &)>;
using UpdateFunc = std::function<void(const sf::Time &)>;
using DrawFunc = std::function<void(sf::RenderTarget &)>;

class Window : private sf::NonCopyable {
public:
	Window(const unsigned int & width, const unsigned int & height, 
			const std::string & title, 
			const unsigned int & fpsTarget,
			const unsigned int & antialiasingLevel);

	~Window();

	void start();
	void stop();

	void setVSync(const bool & val);

	void setEventHandleCallback(const EventFunc & func);
	void setUpdateCallback(const UpdateFunc & func);
	void setDrawCallback(const DrawFunc & func);

	sf::RenderWindow & getHandle();
	const sf::RenderWindow & getHandle() const;

	unsigned int & getLastFPS();
	unsigned int & getLastUPS();

	unsigned int & getWidth();
	unsigned int & getHeight();

private:
	unsigned int mWidth, mHeight;
	std::string mTitle;

	unsigned int mFPSTarget;
	sf::Time mTimePerFrame;

	sf::RenderWindow mWindow;
	
	EventFunc mEventFunc;
	UpdateFunc mUpdateFunc;
	DrawFunc mDrawFunc;

	bool mRunning, mPaused;

	unsigned int mLastFPS, mLastUPS;

private:
	void gameLoop();
};