#include "../stdafx.h"
#include "../Community.h"
#include "MemberLargerOrEqual10Guard.h"

MemberLargerOrEqual10Guard::MemberLargerOrEqual10Guard(shared_ptr<Community> community)
	:community_(community)
{
}

MemberLargerOrEqual10Guard::~MemberLargerOrEqual10Guard()
{
}

bool MemberLargerOrEqual10Guard::Condition(shared_ptr<Event> e)
{
	return community_->GetMembersSize() >= 10;
}