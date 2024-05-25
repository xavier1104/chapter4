#include "stdafx.h"
#include "Event.h"
#include "Waiting.h"

Waiting::Waiting(shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:State(robot, system)
{
}

Waiting::~Waiting()
{
}

void Waiting::HandleEvent(shared_ptr<Event> e)
{
	State::HandleEvent(e);
}
