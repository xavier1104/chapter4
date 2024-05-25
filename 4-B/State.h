#pragma once

#include "StateSystem.h"

class StateSystem;
class Robot;
struct Event;
class State : public StateSystem
{
public:
	State(shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~State();

	virtual void HandleEvent(shared_ptr<Event> e);
	virtual void Exit(shared_ptr<Event> e);
	virtual void Enter(shared_ptr<Event> e);
	void SetStateSystem(shared_ptr<StateSystem> system) { system_ = system; }
	
protected:
	shared_ptr<StateSystem> system_;
	shared_ptr<Robot> robot_;
};