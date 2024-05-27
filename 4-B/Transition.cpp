#include "stdafx.h"
#include "Event.h"
#include "States/State.h"
#include "Guards/Guard.h"
#include "States/FiniteStateMachine.h"
#include "Robot.h"
#include "Actions/Action.h"
#include "Transition.h"

Transition::Transition(shared_ptr<State> from, EventType eventType, shared_ptr<Guard> guard, shared_ptr<Action> action, shared_ptr<State> to)
	: from_(from)
	, eventType_(eventType)
	, guard_(guard)
	, action_(action)
	, to_(to)
{
}

Transition::~Transition()
{
}

void Transition::Transfer(shared_ptr<Event> e, shared_ptr<FiniteStateMachine> fms)
{
	if (eventType_ != e->type_) {
		return;
	}

	shared_ptr<State> current = dynamic_pointer_cast<State>(fms->GetCurrent());
	if (current != from_) {
		return;
	}

	if (guard_ && !guard_->Condition(e)) {
		return;
	}

	current->Exit(e);
	if (action_) {
		action_->Do();
	}
	fms->SetCurrent(to_);
	to_->Enter(e);
}
