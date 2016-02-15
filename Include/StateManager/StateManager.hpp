#pragma once
#include "Common.hpp"
#include "States.hpp"
#include "Context.hpp"
#include "IState.hpp"

class StateManager final : private NonCopyable {
public:
	enum class Action { Clear, Push, Pop };

	explicit StateManager(Context ctx) noexcept;

	void handleEvent(const sf::Event& e) noexcept;
	void update(const sf::Time& dt) noexcept;
	void render(sf::RenderTarget& tgt) const noexcept;

	void pushState(GameState state) noexcept;
	void popState() noexcept;
	void clear() noexcept;

	bool empty() const noexcept;
private:
	auto createState(GameState state) noexcept;
	void applyPendingChanges() noexcept;

	Context mContext;
	friend class IState;
	std::vector<std::unique_ptr<IState>> mStates{ };

	struct PendingChange { Action action; GameState state; };
	std::vector<PendingChange> mPending{ };
};