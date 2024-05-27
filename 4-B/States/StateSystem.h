#pragma once

struct Event;
class StateSystem
{
public:
	StateSystem();
	~StateSystem();
	
	virtual void HandleEvent(shared_ptr<Event> e) = 0;
	virtual void Enter(shared_ptr<Event> e) {};
	virtual void Exit(shared_ptr<Event> e) {};
};