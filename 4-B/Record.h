#pragma once

#include "State.h"

struct Event;
class Recording;
class Waiting;
class Broadcast;
class Record : public State
{
public:
	Record(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Broadcast> broadcast, shared_ptr<Recording> recording, shared_ptr<Waiting> waiting);
	~Record();

	void HandleEvent(shared_ptr<Event> e) override;
	void Enter(shared_ptr<Event> e) override;

private:
	shared_ptr<Broadcast> broadcast_;
	shared_ptr<Recording> recording_;
	shared_ptr<Waiting> waiting_;
};