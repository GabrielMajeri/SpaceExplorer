#pragma once
#include "Common.hpp"
#include "States.hpp"

enum class GameState;
struct Context;

/// This interface represents a game state. All of the member functions are
/// protected, since only the friend class StateManager should call them, or
/// the other states.
class IState : private NonCopyable {
	friend class StateManager;
public:
	explicit IState(StateManager& manager, Context& ctx) noexcept 
		: mManager{ manager }, mContext{ ctx } {};
	virtual ~IState() = default;

	virtual void handleEvent(const sf::Event& e) noexcept = 0;
	virtual void update(const sf::Time& dt) noexcept = 0;
	virtual void render(sf::RenderTarget& target) const noexcept = 0;

protected:
	StateManager& mManager;
	Context& mContext;

	const GameState mType{ GameState::None };
};