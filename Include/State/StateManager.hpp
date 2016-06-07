#pragma once

#include <SFML/Graphics.hpp>
#include "Utility/Context.hpp"
#include "State/State.hpp"

class StateManager
{
public:
	enum class StateID { None, TitleScreen, Running, Paused };

	StateManager(Context& ctx);

	void add(StateID state);
	void pop();
	void clear() noexcept;

	void updateGameState();

	void handleEvent(const sf::Event& ev);
	void update(const float dt);
	void draw(sf::RenderTarget& tgt);

	bool isEmpty() const noexcept;
private:
	friend class State;
	Context& ctx;
	std::vector<std::unique_ptr<State>> stateStack;

	struct Operation
	{
		enum Type { Add, Pop, Clear } type;
		StateID state;

		Operation(Type t, StateID st = StateID::None);
	};
	std::vector<Operation> ops;
};
