#include "stdafx.h"
#include "Event.h"
#include "StateSystem.h"
#include "Transition.h"
#include "Robot.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine(shared_ptr<StateSystem> current, vector<shared_ptr<Transition>> transitions)
	:current_(current)
	,transitions_(transitions)
{
}

FiniteStateMachine::~FiniteStateMachine()
{
}

void FiniteStateMachine::HandleEvent(shared_ptr<Event> e)
{
	current_->HandleEvent(e);
	for (auto& t : transitions_) {
		t->Transfer(e, shared_from_this());
	}

}

void FiniteStateMachine::Enter(shared_ptr<Event> e)
{
	current_->Enter(e);
}

void FiniteStateMachine::Exit(shared_ptr<Event> e)
{
	current_->Exit(e);
}
