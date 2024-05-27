#include "../stdafx.h"
#include "StateSystem.h"
#include "../Robot.h"
#include "Questioning.h"
#include "ThanksForJoining.h"
#include "FiniteStateMachine.h"
#include "KnowledgeKing.h"

KnowledgeKing::KnowledgeKing(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Questioning> questioning, shared_ptr<ThanksForJoining> thanks)
	:State(robot, system)
	,questioning_(questioning)
	,thanks_(thanks)
{
}

KnowledgeKing::~KnowledgeKing()
{
}

void KnowledgeKing::Enter(shared_ptr<Event> e)
{
	if (shared_ptr<FiniteStateMachine> fsm = dynamic_pointer_cast<FiniteStateMachine>(system_)) {
		fsm->SetCurrent(questioning_);
	}

	State::Enter(e);
}