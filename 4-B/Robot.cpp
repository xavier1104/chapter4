#include "stdafx.h"
#include "StateSystem.h"
#include "Event.h"
#include "Broadcast.h"
#include "ChatRoom.h"
#include "Forum.h"
#include "Comment.h"
#include "Speak.h"
#include "Message.h"
#include "Comment.h"
#include "Robot.h"

Robot::Robot(shared_ptr<Broadcast> broadcast, shared_ptr<ChatRoom> chartroom, shared_ptr<Forum> forum)
	:broadcast_(broadcast)
	,chatroom_(chatroom_)
	,forum_(forum)
	,id_("bot")
	,quota_(20)
{
}

Robot::~Robot()
{
}

void Robot::HandleEvent(shared_ptr<Event> e)
{
	system_->HandleEvent(e);
}

bool Robot::Broadcasting(string content)
{
	if (broadcast_->GoBroadcast(id_)) {
		shared_ptr<Speak> speak = make_shared<Speak>(content);
		broadcast_->Speaking(id_, speak);
		broadcast_->StopBroadcast(id_);
		return true;
	}
	return false;
}

void Robot::Chatting(string content, vector<string> tags)
{
	shared_ptr<Message> message = make_shared<Message>(content, tags);
	chatroom_->Send(id_, message);
}

void Robot::AddComment(string postId, string content, vector<string> tags)
{
	shared_ptr<Comment> comment = make_shared<Comment>(postId, content, tags);
	forum_->AddComment(id_, comment);
}
