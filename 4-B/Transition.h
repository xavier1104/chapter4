#pragma once

class State;
class Guard;
class FiniteStateMachine;
class Robot;
class Action;
class Transition
{
public:
	Transition(shared_ptr<State> from, EventType eventType, shared_ptr<Guard> guard, shared_ptr<Action> action, shared_ptr<State> to);
	~Transition();

	void Transfer(shared_ptr<Event> e, shared_ptr<FiniteStateMachine> fms);
private:
	shared_ptr<State> from_;
	shared_ptr<State> to_;
	EventType eventType_;
	shared_ptr<Guard> guard_;
	shared_ptr<Action> action_;
};