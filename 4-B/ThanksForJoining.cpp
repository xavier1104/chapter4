#include "stdafx.h"
#include "State.h"
#include "Event.h"
#include "Community.h"
#include "Robot.h"
#include "ThanksForJoining.h"

ThanksForJoining::ThanksForJoining(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	: State(robot, system)
	, targetTime_(20)
	,elapsedTime_(0)
	,community_(community)
{
}

ThanksForJoining::~ThanksForJoining()
{
}

void ThanksForJoining::HandleEvent(shared_ptr<Event> e)
{
	if (shared_ptr<TimeElapsedEvent> timeEvent = dynamic_pointer_cast<TimeElapsedEvent>(e)) {
		elapsedTime_ += timeEvent->GetSeconds();
		if (elapsedTime_ >= targetTime_) {
			community_->HandleEvent(make_shared<ThanksFinishedEvent>());
		}
	}

	State::HandleEvent(e);
}

void ThanksForJoining::Enter(shared_ptr<Event> e)
{
	elapsedTime_ = 0;
	if (shared_ptr<QuestionFinishedEvent> qf = dynamic_pointer_cast<QuestionFinishedEvent>(e)) {
		string msg;
		if (qf->winnerId_.empty()) {
			msg = "Tie!";
		}
		else {
			msg = "The winner is " + qf->winnerId_;
		}
		if (!robot_->Broadcasting(msg)) {
			robot_->Chatting(msg);
		}
	}

	State::Enter(e);
}