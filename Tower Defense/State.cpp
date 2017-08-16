#include "State.hpp"
#include "StateManager.hpp"

State::State(StateManager &stack, States::Context context)
	: stack(stack)
	, context(context)
{
}

void State::pushState(States::ID state) const
{
	stack.pushState(state);
}

void State::popState() const
{
	stack.popState();
}

void State::clearStates() const
{
	stack.clearStates();
}

States::Context State::getContext() const
{
	return context;
}