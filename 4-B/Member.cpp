#include "stdafx.h"
#include "Broadcast.h"
#include "ChatRoom.h"
#include "Message.h"
#include "Member.h"

Member::Member(string& id, Permission permission)
	:id_(id)
	,logState_(Logout)
	,permission_(permission)
{
}

Member::~Member()
{
}

void Member::GoBrocast(shared_ptr<Broadcast> broadcast)
{
	broadcast->GoBroadcast(id_);
}

void Member::Send(shared_ptr<ChatRoom> chatroom, shared_ptr<Message> msg)
{
	chatroom->Send(id_, msg);
}
