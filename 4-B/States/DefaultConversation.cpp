#include "../stdafx.h"
#include "../Event.h"
#include "State.h"
#include "../utility.h"
#include "../Robot.h"
#include "DefaultConversation.h"

DefaultConversation::DefaultConversation(shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:State(robot, system)
{
}

DefaultConversation::~DefaultConversation()
{
}

void DefaultConversation::HandleEvent(shared_ptr<Event> e)
{
	if (shared_ptr<NewMessageEvent> msgEvent = dynamic_pointer_cast<NewMessageEvent>(e)) {
		HandleNewMessage(msgEvent);
	}
	else if (shared_ptr<NewPostEvent> postEvent = dynamic_pointer_cast<NewPostEvent>(e)) {
		HandleNewPost(postEvent);
	}

	State::HandleEvent(e);
}

void DefaultConversation::HandleNewMessage(shared_ptr<NewMessageEvent> e)
{
	static int idx = 0;
	static vector<string> reply = { "good to hear", "thank you", "How are you" };
	robot_->Chatting(reply[idx], { e->authorId_ });
	idx++;
	idx %= reply.size();
}

void DefaultConversation::HandleNewPost(shared_ptr<NewPostEvent> e)
{
	robot_->AddComment(e->id_, "Nice post", { e->authorId_ });
}