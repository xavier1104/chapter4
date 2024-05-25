#pragma once

#include "State.h"

class StateSystem;
class Robot;
class Questioning;
class ThanksForJoining;
class KnowledgeKing : public State
{
public:
	KnowledgeKing(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Questioning> questioning, shared_ptr<ThanksForJoining> thanks);
	~KnowledgeKing();

	void Enter(shared_ptr<Event> e);

private:
	shared_ptr<Questioning> questioning_;
	shared_ptr<ThanksForJoining> thanks_;
};