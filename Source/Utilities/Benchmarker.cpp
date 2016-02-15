#include "Common.hpp"
#include "Utilities/Benchmarker.hpp"

Benchmarker::Benchmarker(const sf::Time& duration) noexcept
	: mDuration{ duration }
{
	// Time should not be zero, because it could waste a lot of resources
	assert(mDuration != sf::Time::Zero);
}

void Benchmarker::start() noexcept
{
	// The clock should not be started twice
	assert(!mIsStarted);

	mIsStarted = true;
	mClock.restart();
}

void Benchmarker::stop() noexcept
{
	// Cannot stop clock if not yet started
	assert(mIsStarted);

	mIsStarted = false;
	mClock.restart();
}

void Benchmarker::restart(const sf::Time& duration) noexcept
{
	// Time should not be zero, because it could waste a lot of resources
	assert(mDuration != sf::Time::Zero);
	mDuration = duration;
	mIsStarted = true;
	mUpdates = mFrames = 0;

	// Restart the clock
	mClock.restart();
}

void Benchmarker::addUpdate() noexcept
{
	// Nothing to do if not yet started
	if (!mIsStarted)
		return;

	++mUpdates;

	if (mClock.getElapsedTime() >= mDuration) {
		// Print results to console
		std::cout << " Benchmark ran for " << mDuration.asSeconds()
			<< " seconds.\n  UPS(avg): " << (mUpdates / mDuration.asSeconds())
			<< "\n  FPS(avg): " << (mFrames / mDuration.asSeconds()) 
			<< std::endl;

		// Reset the clock
		mUpdates = mFrames = 0u;
		mClock.restart();
	}
}

void Benchmarker::addFrame() noexcept
{
	// Nothing to do if stopped
	if (!mIsStarted)
		return;

	++mFrames;
}
