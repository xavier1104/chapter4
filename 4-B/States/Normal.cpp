#include "../stdafx.h"
#include "State.h"
#include "StateSystem.h"
#include "../Event.h"
#include "../Robot.h"
#include "../Commands/Command.h"
#include "FiniteStateMachine.h"
#include "../Community.h"
#include "DefaultConversation.h"
#include "Interacting.h"
#include "Normal.h"

Normal::Normal(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Community> community, shared_ptr<DefaultConversation> dc, shared_ptr<Interacting> interacting)
	:State(robot, system)
	,community_(community)
	,dc_(dc)
	,interacting_(interacting)
{
}

Normal::~Normal()
{
}

void Normal::Enter(shared_ptr<Event> e)
{
	if (shared_ptr<FiniteStateMachine> fsm = dynamic_pointer_cast<FiniteStateMachine>(system_)) {
		if (community_->GetMembersSize() >= 10) {
			fsm->SetCurrent(interacting_);
		}
		else {
			fsm->SetCurrent(dc_);
		}
	}

	State::Enter(e);
}

