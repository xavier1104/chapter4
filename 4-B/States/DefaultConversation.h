#pragma once

class State;
class Robot;
class DefaultConversation : public State
{
public:
	DefaultConversation(shared_ptr<Robot> robot, shared_ptr<StateSystem> system);
	~DefaultConversation();

	void HandleEvent(shared_ptr<Event> e) override;

private:
	void HandleNewMessage(shared_ptr<NewMessageEvent> e);
	void HandleNewPost(shared_ptr<NewPostEvent> e);
};