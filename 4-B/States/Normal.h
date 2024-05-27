#pragma once

class State;
class StateSystem;
class Robot;
class Command;
class Community;
class DefaultConversation;
class Interacting;
struct Event;
class Normal : public State
{
public:
	Normal(shared_ptr<Robot> robot, shared_ptr<StateSystem> system, shared_ptr<Community> community, shared_ptr<DefaultConversation> dc, shared_ptr<Interacting> interacting);
	~Normal();

	void Enter(shared_ptr<Event> e);
	
private:
	shared_ptr<Community> community_;
	shared_ptr<DefaultConversation> dc_;
	shared_ptr<Interacting> interacting_;
};