#pragma once

#include "State.h"

class Community;
class Robot;
class StateSystem;
struct Event;
class Questioning : public State
{
public:
	Questioning(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~Questioning();

	void HandleEvent(shared_ptr<Event> e) override;
	void Enter(shared_ptr<Event> e) override;
	string GetWinnerId();

private:
	int idx_;
	static vector<pair<string, string>> questions_;
	shared_ptr<Community> community_;
	map<string, int> scores_;
};