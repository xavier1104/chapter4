#pragma once

#include "State.h"

struct Event;

class Recording : public State
{
public:
	Recording(shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~Recording();

	string GetRecorderId() { return recorderId_; }
	void HandleEvent(shared_ptr<Event> e);

	void Enter(shared_ptr<Event> e);

private:
	void Replay();

private:
	vector<string> records_;
	string recorderId_;
};