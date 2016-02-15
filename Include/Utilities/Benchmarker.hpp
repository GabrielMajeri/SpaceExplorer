#pragma once
#include "Common.hpp"

class Benchmarker final : private NonCopyable {
public:
	/// Constructs a new FPS and UPS benchmarker that prints statistics
	/// every [duration] that passes.
	explicit Benchmarker(const sf::Time& duration) noexcept;

	/// Starts the clock.
	void start() noexcept;
	/// Stops the clock.
	void stop() noexcept;

	/// Restarts the clock with a different duration.
	void restart(const sf::Time& duration) noexcept;

	/// Adds an update to the counter.
	void addUpdate() noexcept; 
	/// Adds a frame to the counter.
	void addFrame() noexcept;

private:
	sf::Time mDuration{ };

	/// Whether the clock is started or not
	bool mIsStarted{ false };
	sf::Clock mClock{ };

	size_t mFrames{ 0u }, mUpdates{ 0u };
};