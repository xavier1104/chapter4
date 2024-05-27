#include "../stdafx.h"
#include "../Event.h"
#include "../Broadcast.h"
#include "Waiting.h"
#include "Recording.h"
#include "FiniteStateMachine.h"
#include "Record.h"

Record::Record(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Broadcast> broadcast, shared_ptr<Recording> recording, shared_ptr<Waiting> waiting)
	:State(robot, system)
	,broadcast_(broadcast)
	,waiting_(waiting)
	,recording_(recording)
{
}

Record::~Record()
{
}

void Record::HandleEvent(shared_ptr<Event> e)
{
	State::HandleEvent(e);
}

void Record::Enter(shared_ptr<Event> e)
{
	if (shared_ptr<FiniteStateMachine> fsm = dynamic_pointer_cast<FiniteStateMachine>(system_)) {
		if (broadcast_->GetState() == Broadcast::Broadcasting) {
			fsm->SetCurrent(recording_);
		}
		else {
			fsm->SetCurrent(waiting_);
		}
	}

	State::Enter(e);
}
