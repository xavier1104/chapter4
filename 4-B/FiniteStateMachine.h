#pragma once

#include "StateSystem.h"

class StateSystem;
class Transition;
class FiniteStateMachine : public StateSystem, public enable_shared_from_this<FiniteStateMachine>
{
public:
	FiniteStateMachine(shared_ptr<StateSystem> current, vector<shared_ptr<Transition>> transitions);
	~FiniteStateMachine();

	void HandleEvent(shared_ptr<Event> e) override;
	void Enter(shared_ptr<Event> e) override;
	void Exit(shared_ptr<Event> e) override;

	shared_ptr<StateSystem> GetCurrent() { return current_; }
	void SetCurrent(shared_ptr<StateSystem> state) { current_ = state; }
private:
	shared_ptr<StateSystem> current_;
	vector<shared_ptr<Transition>> transitions_;
};