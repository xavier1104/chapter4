#include "stdafx.h"
#include "Event.h"
#include "GuardArgs.h"
#include "ActionArgs.h"
#include "FiniteStateMachine.h"
#include "State.h"
#include "Transition.h"
#include "Normal.h"
#include "Record.h"
#include "KnowledgeKing.h"
#include "DefaultConversation.h"
#include "Interacting.h"
#include "Recording.h"
#include "Waiting.h"
#include "Questioning.h"
#include "ThanksForJoining.h"
#include "Guard.h"
#include "CommandGuard.h"
#include "MemberLargerOrEqual10Guard.h"
#include "MemberLessThan10Guard.h"
#include "TimeElapsedGuard.h"
#include "Community.h"
#include "Robot.h"
#include "Command.h"
#include "KingCommand.h"
#include "PlayAgainCommand.h"
#include "KingStopCommand.h"
#include "RecordCommand.h"
#include "StopRecordingCommand.h"
#include "Action.h"
#include "CommandAction.h"
#include "DataType.h"
#include "RobotFSMFacade.h"

STransition::STransition(eState from, EventType e, shared_ptr<SGuard>guard, shared_ptr<SAction> action, eState to)
	:from_(from)
	,e_(e)
	,guard_(guard)
	,action_(action)
	,to_(to)
{

}

RobotFSMFacade::RobotFSMFacade(shared_ptr<Robot> robot, shared_ptr<Community> community, shared_ptr<Broadcast> broadcast)
	:root_(nullptr)
	,robot_(robot)
	,community_(community)
	,broadcast_(broadcast)
{
	dc_ = make_shared<DefaultConversation>(robot_, nullptr);
	interacting_ = make_shared<Interacting>(community_, robot_, nullptr);
	recording_ = make_shared<Recording>(robot_, nullptr);
	waiting_ = make_shared<Waiting>(robot_, nullptr);
	questioning_ = make_shared<Questioning>(community_, robot_, nullptr);
	thanks_ = make_shared<ThanksForJoining>(community_, robot_, nullptr);
	normal_ = make_shared<Normal>(robot_, nullptr, community_, dc_, interacting_);
	record_ = make_shared<Record>(robot_, nullptr, broadcast_, recording_, waiting_);
	king_ = make_shared<KnowledgeKing>(robot_, nullptr, questioning_, thanks_);

	kingCmd_ = make_shared<KingCommand>();
	playAgainCmd_ = make_shared<PlayAgainCommand>(robot_);
	kingStopCmd_ = make_shared<KingStopCommand>();
	recordCmd_ = make_shared<RecordCommand>();
	stopRecordingCmd_ = make_shared<StopRecordingCommand>(recording_, community_);
}

RobotFSMFacade::~RobotFSMFacade()
{
}

void RobotFSMFacade::CreateRootFSM(eState init, vector<shared_ptr<STransition>> transitions)
{
	root_ = GetFSM(init, transitions);
}

void RobotFSMFacade::CreateNodeFSM(eState parent, eState init, vector<shared_ptr<STransition>> transitions)
{
	shared_ptr<FiniteStateMachine> fsm = GetFSM(init, transitions);
	shared_ptr<State> state = GetState(parent);
	state->SetStateSystem(fsm);
}

void RobotFSMFacade::Finish()
{
	root_->Enter(nullptr);
	robot_->SetStateSystem(root_);
}

shared_ptr<FiniteStateMachine> RobotFSMFacade::GetFSM(eState init, vector<shared_ptr<STransition>> transitions)
{
	shared_ptr<State> current = GetState(init);
	vector<shared_ptr<Transition>> ts;
	for (auto& t : transitions) {
		shared_ptr<Transition> transition = GetTransition(t);
		ts.emplace_back(transition);
	}

	return make_shared<FiniteStateMachine>(current, ts);
}

shared_ptr<State> RobotFSMFacade::GetState(eState state)
{
	switch (state)
	{
	case eS_Normal:
	{
		return normal_;
	}
	case eS_Record:
	{
		return record_;
	}
	case eS_KnowledgeKing:
	{
		return king_;
	}
	case eS_DefaultConversation:
	{
		return dc_;
	}
	case eS_Interacting:
	{
		return interacting_;
	}
	case eS_Recording:
	{
		return recording_;
	}
	case eS_Waiting:
	{
		return waiting_;
	}
	case eS_Questioning:
	{
		return questioning_;
	}
	case eS_ThanksForJoining:
	{
		return thanks_;
	}
	default:
		return nullptr;
	}
}

shared_ptr<Transition> RobotFSMFacade::GetTransition(shared_ptr<STransition> transition)
{
	shared_ptr<State> from = GetState(transition->from_);
	shared_ptr<Guard> guard = GetGuard(transition->guard_);
	shared_ptr<Action> action = GetAction(transition->action_);
	shared_ptr<State> to = GetState(transition->to_);

	return make_shared<Transition>(from, transition->e_, guard, action, to);
}

shared_ptr<Guard> RobotFSMFacade::GetGuard(shared_ptr<SGuard> guard)
{
	if (shared_ptr<SCommandGuard> g = dynamic_pointer_cast<SCommandGuard>(guard)) {
		shared_ptr<Command> cmd = GetCommand(g->cmd_);
		return make_shared<CommandGuard>(cmd, community_, robot_);
	}
	else if (shared_ptr<SMemberLargerOrEqual10Guard> g = dynamic_pointer_cast<SMemberLargerOrEqual10Guard>(guard)) {
		return make_shared<MemberLargerOrEqual10Guard>(community_);
	}
	else if (shared_ptr<SMemberLessThan10Guard> g = dynamic_pointer_cast<SMemberLessThan10Guard>(guard)) {
		return make_shared<MemberLessThan10Guard>(community_);
	}
	else if (shared_ptr<STimeElapsedGuard> g = dynamic_pointer_cast<STimeElapsedGuard>(guard)) {
		return make_shared<TimeElapsedGuard>(g->seconds_);
	}
	
	return nullptr;
}

shared_ptr<Command> RobotFSMFacade::GetCommand(eCommand cmd)
{
	switch (cmd)
	{
	case eC_King:
	{
		return kingCmd_;
	}
	case eC_KingStop:
	{
		return kingStopCmd_;
	}
	case eC_PlayAgain:
	{
		return playAgainCmd_;
	}
	case eC_Record:
	{
		return recordCmd_;
	}
	case eC_StopRecording:
	{
		return stopRecordingCmd_;
	}
	default:
		return nullptr;
	}
}

shared_ptr<Action> RobotFSMFacade::GetAction(shared_ptr<SAction> action)
{
	if (shared_ptr<SCommandAction> a = dynamic_pointer_cast<SCommandAction>(action)) {
		shared_ptr<Command> cmd = GetCommand(a->cmd_);
		return make_shared<CommandAction>(cmd, robot_);
	}

	return nullptr;
}
