#pragma once

class Broadcast;
class Message;
class ChatRoom;
class Member : public enable_shared_from_this<Member>
{
public:
	enum LogState
	{
		Login = 0,
		Logout
	};

	enum Permission
	{
		NormalMember = 0,
		Admin
	};

public:
	Member(string& id, Permission permission);
	~Member();
	
	void GoBrocast(shared_ptr<Broadcast> broadcast);
	void Send(shared_ptr<ChatRoom> chatroom, shared_ptr<Message> msg);
	string GetID() { return id_; }
	void SetLogState(LogState state) { logState_ = state; }
	Permission GetPermission() { return permission_; }
private:
	string id_;
	LogState logState_;
	Permission permission_;
};