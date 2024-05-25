#pragma once

class StateSystem;
class Broadcast;
class ChatRoom;
class Forum;
struct Event;
class Robot
{
public:
	Robot(shared_ptr<Broadcast> broadcast, shared_ptr<ChatRoom> chartroom, shared_ptr<Forum> forum);
	~Robot();

	void SetStateSystem(shared_ptr<StateSystem> system) { system_ = system; }
	void HandleEvent(shared_ptr<Event> e);
	bool Broadcasting(string content);
	void Chatting(string content, vector<string> tags = {});
	void AddComment(string postId, string content, vector<string> tags = {});
	int GetQuota() { return quota_; }
	void CostQuota(int cost) { quota_ -= cost; }
private:
	string id_;
	int quota_;
	shared_ptr<StateSystem> system_;
	shared_ptr<Broadcast> broadcast_;
	shared_ptr<ChatRoom> chatroom_;
	shared_ptr<Forum> forum_;
};