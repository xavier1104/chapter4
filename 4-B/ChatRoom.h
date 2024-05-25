#pragma once

class Message;
class ChatRoom
{
public:
	ChatRoom();
	~ChatRoom();

	void Send(string senderId, shared_ptr<Message> msg);
};