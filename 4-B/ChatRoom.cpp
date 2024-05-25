#include "stdafx.h"
#include "Message.h"
#include "Member.h"
#include "utility.h"
#include "ChatRoom.h"

ChatRoom::ChatRoom()
{
}

ChatRoom::~ChatRoom()
{
}

void ChatRoom::Send(string senderId, shared_ptr<Message> msg)
{
	if (senderId == "bot") {
		cout << "🤖: " << msg->GetContent() << " " << GetTagStr(msg->GetTags()) << '\n';
	}
	else {
		cout << "💬 " << senderId << ": " << msg->GetContent() << " " << GetTagStr(msg->GetTags()) << '\n';
	}
}
