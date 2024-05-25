#include "stdafx.h"
#include "Member.h"
#include "ChatRoom.h"
#include "Forum.h"
#include "Message.h"
#include "Post.h"
#include "Speak.h"
#include "Broadcast.h"
#include "Robot.h"
#include "Community.h"

Community::Community(shared_ptr<Robot> robot, shared_ptr<Broadcast> broadcast, shared_ptr<ChatRoom> chatroom, shared_ptr<Forum> forum)
	:robot_(robot)
	,broadcast_(broadcast)
	,chatroom_(chatroom)
	,forum_(forum)
{
}

Community::~Community()
{
}

void Community::OnLogin(shared_ptr<LoginEvent> e)
{
	shared_ptr<Member> member = make_shared<Member>(e->userId_, e->isAdmin_? Member::Admin : Member::NormalMember);
	member->SetLogState(Member::Login);
	members_.emplace(e->userId_, member);
	robot_->HandleEvent(e);
}

void Community::OnLogout(shared_ptr<LogoutEvent> e)
{
	if (shared_ptr<Member> member = GetMember(e->userId_)) {
		member->SetLogState(Member::Logout);
		members_.erase(member->GetID());
		robot_->HandleEvent(e);
	}
}

void Community::OnNewMessage(shared_ptr<NewMessageEvent> e)
{
	if (shared_ptr<Member> member = GetMember(e->authorId_)) {
		shared_ptr<Message> msg = make_shared<Message>(e->content_, e->tags_);
		chatroom_->Send(member->GetID(), msg);
		robot_->HandleEvent(e);
	}
}

void Community::OnNewPost(shared_ptr<NewPostEvent> e)
{
	if (shared_ptr<Member> member = GetMember(e->authorId_)) {
		shared_ptr<Post> post = make_shared<Post>(e->id_, e->title_, e->content_, e->tags_);
		forum_->SendPost(member->GetID(), post);
		robot_->HandleEvent(e);
	}
}

void Community::OnGoBroadcasting(shared_ptr<GoBroadcastingEvent> e)
{
	if (shared_ptr<Member> member = GetMember(e->speakerId_)) {
		broadcast_->GoBroadcast(member->GetID());
		robot_->HandleEvent(e);
	}
}

void Community::OnSpeak(shared_ptr<SpeakEvent> e)
{
	if (shared_ptr<Member> member = GetMember(e->speakerId_)) {
		shared_ptr<Speak> speak = make_shared<Speak>(e->content_);
		broadcast_->Speaking(member->GetID(), speak);
		robot_->HandleEvent(e);
	}
}

void Community::OnStopBroadcasting(shared_ptr<StopBroadcastingEvent> e)
{	
	if (shared_ptr<Member> member = GetMember(e->speakerId_)) {
		broadcast_->StopBroadcast(member->GetID());
		robot_->HandleEvent(e);
	}
}

void Community::OnTimeElapsed(shared_ptr<TimeElapsedEvent> e)
{
	cout << "🕑 " << e->time_ << ' ' << e->GetUnitStr() << " elapsed...\n";
	robot_->HandleEvent(e);
}

void Community::OnQuestionFinished(shared_ptr<QuestionFinishedEvent> e)
{
	robot_->HandleEvent(e);
}

void Community::OnThanksFinished(shared_ptr<ThanksFinishedEvent> e)
{
	robot_->HandleEvent(e);
}

void Community::OnStopRecording(shared_ptr<StopRecordingEvent> e)
{
	robot_->HandleEvent(e);
}

void Community::HandleEvent(shared_ptr<Event> eventArgs)
{
	switch (eventArgs->type_)
	{
	case eET_Started:
	{
		
		break;
	}
	case eET_Login:
	{
		if (shared_ptr<LoginEvent> e = dynamic_pointer_cast<LoginEvent>(eventArgs)) {
			OnLogin(e);
		}
		break;
	}
	case eET_Logout:
	{
		if (shared_ptr<LogoutEvent> e = dynamic_pointer_cast<LogoutEvent>(eventArgs)) {
			OnLogout(e);
		}
		break;
	}
	case eET_TimeElapsed:
	{
		if (shared_ptr<TimeElapsedEvent> e = dynamic_pointer_cast<TimeElapsedEvent>(eventArgs)) {
			OnTimeElapsed(e);
		}
		break;
	}
	case eET_NewMessage:
	{
		if (shared_ptr<NewMessageEvent> e = dynamic_pointer_cast<NewMessageEvent>(eventArgs)) {
			OnNewMessage(e);
		}
		break;
	}
	case eET_NewPost:
	{
		if (shared_ptr<NewPostEvent> e = dynamic_pointer_cast<NewPostEvent>(eventArgs)) {
			OnNewPost(e);
		}
		break;
	}
	case eET_GoBroadcasting:
	{
		if (shared_ptr<GoBroadcastingEvent> e = dynamic_pointer_cast<GoBroadcastingEvent>(eventArgs)) {
			OnGoBroadcasting(e);
		}
		break;
	}
	case eET_Speak:
	{
		if (shared_ptr<SpeakEvent> e = dynamic_pointer_cast<SpeakEvent>(eventArgs)) {
			OnSpeak(e);
		}
		break;
	}
	case eET_StopBroadcasting:
	{
		if (shared_ptr<StopBroadcastingEvent> e = dynamic_pointer_cast<StopBroadcastingEvent>(eventArgs)) {
			OnStopBroadcasting(e);
		}
		break;
	}
	case eET_QuestionFinished:
	{
		if (shared_ptr<QuestionFinishedEvent> e = dynamic_pointer_cast<QuestionFinishedEvent>(eventArgs)) {
			OnQuestionFinished(e);
		}
		break;
	}
	case eET_ThanksFinished:
	{
		if (shared_ptr<ThanksFinishedEvent> e = dynamic_pointer_cast<ThanksFinishedEvent>(eventArgs)) {
			OnThanksFinished(e);
		}
		break;
	}
	case eET_StopRecording:
	{
		if (shared_ptr<StopRecordingEvent> e = dynamic_pointer_cast<StopRecordingEvent>(eventArgs)) {
			OnStopRecording(e);
		}
		break;
	}
	case eET_End:
	{
		
		break;
	}
	}
}

shared_ptr<Member> Community::GetMember(string id)
{
	auto&& it = members_.find(id);
	if (it == members_.end()) {
		return nullptr;
	}

	return it->second;
}
