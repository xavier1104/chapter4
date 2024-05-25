#pragma once

class Normal;
class Record;
class KnowledgeKing;
class Community;
class Broadcast;
class Robot;
class Action;
class Guard;
class Command;
class Transition;
class State;
class Normal;
class Record;
class KnowledgeKing;
class DefaultConversation;
class Interacting;
class Recording;
class Waiting;
class Questioning;
class ThanksForJoining;
class KingCommand;
class PlayAgainCommand;
class KingStopCommand;
class RecordCommand;
class StopRecordingCommand;
class FiniteStateMachine;

struct SGuard;
struct SAction;

struct STransition
{
	STransition(eState from, EventType e, shared_ptr<SGuard>guard, shared_ptr<SAction> action, eState to);

	eState from_;
	EventType e_;
	shared_ptr<SGuard> guard_;
	shared_ptr<SAction> action_;
	eState to_;
};

class RobotFSMFacade
{

public:
	RobotFSMFacade(shared_ptr<Robot> robot, shared_ptr<Community> community, shared_ptr<Broadcast> broadcast);
	~RobotFSMFacade();

	void CreateRootFSM(eState init, vector<shared_ptr<STransition>> transitions);

	void CreateNodeFSM(eState parent, eState init, vector<shared_ptr<STransition>> transitions);

	void Finish();

private:
	shared_ptr<FiniteStateMachine> GetFSM(eState init, vector<shared_ptr<STransition>> transitions);
	
	shared_ptr<State> GetState(eState state);

	shared_ptr<Transition> GetTransition(shared_ptr<STransition> transition);

	shared_ptr<Guard> GetGuard(shared_ptr<SGuard> guard);

	shared_ptr<Command> GetCommand(eCommand cmd);

	shared_ptr<Action> GetAction(shared_ptr<SAction> action);

private:
	shared_ptr<Community> community_;
	shared_ptr<Broadcast> broadcast_;
	shared_ptr<Robot> robot_;

	shared_ptr<FiniteStateMachine> root_;

	shared_ptr<Normal> normal_;
	shared_ptr<Record> record_;
	shared_ptr<KnowledgeKing> king_;
	shared_ptr<DefaultConversation> dc_;
	shared_ptr<Interacting> interacting_;
	shared_ptr<Recording> recording_;
	shared_ptr<Waiting> waiting_;
	shared_ptr<Questioning> questioning_;
	shared_ptr<ThanksForJoining> thanks_;

	shared_ptr<KingCommand> kingCmd_;
	shared_ptr<PlayAgainCommand> playAgainCmd_;
	shared_ptr<KingStopCommand> kingStopCmd_;
	shared_ptr<RecordCommand> recordCmd_;
	shared_ptr<StopRecordingCommand> stopRecordingCmd_;
};