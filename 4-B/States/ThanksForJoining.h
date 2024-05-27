#pragma once

#include "State.h"

class ThanksForJoining : public State
{
public:
	ThanksForJoining(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~ThanksForJoining();

	void HandleEvent(shared_ptr<Event> e) override;
	void Enter(shared_ptr<Event> e) override;
private:
	int targetTime_;
	int elapsedTime_;
	shared_ptr<Community> community_;
};