#pragma once

class State;
class Interacting : public State
{
public:
	Interacting(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~Interacting();

	void HandleEvent(shared_ptr<Event> e) override;

private:
	void HandleNewMessage(shared_ptr<NewMessageEvent> e);
	void HandleNewPost(shared_ptr<NewPostEvent> e);

private:
	shared_ptr<Community> community_;
};