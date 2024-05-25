#pragma once

#include "Event.h"

class ChatRoom;
class Forum;
class Broadcast;
class Member;
class Robot;
class Community
{
public:
	Community(shared_ptr<Robot> robot, shared_ptr<Broadcast> broadcast, shared_ptr<ChatRoom> chatroom, shared_ptr<Forum> forum);
	~Community();

	void HandleEvent(shared_ptr<Event> e);
	size_t GetMembersSize() { return members_.size() + 1; }
	map<string, shared_ptr<Member>> GetMembers() { return members_; }
	shared_ptr<Member> GetMember(string id);

private:
	void OnLogin(shared_ptr<LoginEvent> e);
	void OnLogout(shared_ptr<LogoutEvent> e);
	void OnNewMessage(shared_ptr<NewMessageEvent> e);
	void OnNewPost(shared_ptr<NewPostEvent> e);
	void OnGoBroadcasting(shared_ptr<GoBroadcastingEvent> e);
	void OnSpeak(shared_ptr<SpeakEvent> e);
	void OnStopBroadcasting(shared_ptr<StopBroadcastingEvent> e);
	void OnTimeElapsed(shared_ptr<TimeElapsedEvent> e);
	void OnQuestionFinished(shared_ptr<QuestionFinishedEvent> e);
	void OnThanksFinished(shared_ptr<ThanksFinishedEvent> e);
	void OnStopRecording(shared_ptr<StopRecordingEvent> e);
private:
	map<string, shared_ptr<Member>> members_;
	shared_ptr<ChatRoom> chatroom_;
	shared_ptr<Forum> forum_;
	shared_ptr<Broadcast> broadcast_;
	shared_ptr<Robot> robot_;
};