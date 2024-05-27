#include "../stdafx.h"
#include "State.h"
#include "../Event.h"
#include "../utility.h"
#include "../Community.h"
#include "../Robot.h"
#include "Interacting.h"

Interacting::Interacting(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:State(robot, system)
	,community_(community)
{
}

Interacting::~Interacting()
{
}

void Interacting::HandleEvent(shared_ptr<Event> e)
{
	if (shared_ptr<NewMessageEvent> msgEvent = dynamic_pointer_cast<NewMessageEvent>(e)) {
		HandleNewMessage(msgEvent);
	}
	else if (shared_ptr<NewPostEvent> postEvent = dynamic_pointer_cast<NewPostEvent>(e)) {
		HandleNewPost(postEvent);
	}

	State::HandleEvent(e);
}

void Interacting::HandleNewMessage(shared_ptr<NewMessageEvent> e)
{
	static int idx = 0;
	static vector<string> reply = { "Hi hi😁", "I like your idea!" };
	robot_->Chatting(reply[idx], { e->authorId_ });
	idx++;
	idx %= reply.size();
}

void Interacting::HandleNewPost(shared_ptr<NewPostEvent> e)
{
	vector<string> tags = {"bot"};
	for (auto&& [userId, member] : community_->GetMembers()) {
		tags.emplace_back(userId);
	}
	robot_->AddComment(e->id_, "How do you guys think about it?", tags);
}