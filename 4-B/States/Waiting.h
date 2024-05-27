#pragma once

#include "State.h"

struct Event;

class Waiting : public State
{
public:
	Waiting(shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~Waiting();

	void HandleEvent(shared_ptr<Event> e);
};