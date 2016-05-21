#include "State/StateManager.hpp"

#include <cassert>

#include "State/TitleScreen.hpp"
#include "State/Running.hpp"
#include "State/Paused.hpp"

StateManager::Operation::Operation(Type t, StateID st)
: type{ t }, state{ st }
{
}

StateManager::StateManager(Context& ctx)
: ctx{ ctx }
{

}

void StateManager::add(StateID id)
{
	ops.push_back(Operation{Operation::Add, id});

	if(stateStack.empty())
		updateGameState();
}

void StateManager::pop()
{
	if(stateStack.empty())
				throw std::logic_error{ "[STATES] Cannot pop state from stack, no current state." };

	ops.push_back({ Operation::Pop, StateID::None });
}

void StateManager::clear() noexcept
{
	ops.push_back(Operation{Operation::Clear, StateID::None});
}

#include <iostream>
void StateManager::updateGameState()
{
	for(const auto& nextOp : ops)
	{
		switch(nextOp.type)
		{
		case Operation::Add:
			{
				switch(nextOp.state)
				{
				case StateID::TitleScreen:
					stateStack.emplace_back(std::make_unique<TitleScreen>(*this));
					break;

				case StateID::Running:
					stateStack.emplace_back(std::make_unique<RunningState>(*this));
					break;

				case StateID::Paused:
					stateStack.emplace_back(std::make_unique<PausedState>(*this));
					break;

				default:
					throw std::logic_error{ "[STATES] Could not create game state." };
				}
			}
			break;
		case Operation::Pop:
			stateStack.pop_back();
			break;

		case Operation::Clear:
			stateStack.clear();
			break;

		default:
			throw std::logic_error{ "[STATES] Unknown state change operation." };
			break;
		}
	}

	ops.clear();
}

void StateManager::handleEvent(const sf::Event& ev)
{
	assert(!stateStack.empty());
	stateStack.back()->handleEvent(ev);
}

void StateManager::update(const float dt)
{
	assert(!stateStack.empty());
	stateStack.back()->update(dt);
}

void StateManager::draw(sf::RenderTarget& tgt)
{
	assert(!stateStack.empty());
	stateStack.back()->draw(tgt);
}
