#include "stdafx.h"
#include "Guard.h"
#include "Community.h"
#include "MemberLessThan10Guard.h"

MemberLessThan10Guard::MemberLessThan10Guard(shared_ptr<Community> community)
	:community_(community)
{
}

MemberLessThan10Guard::~MemberLessThan10Guard()
{
}

bool MemberLessThan10Guard::Condition(shared_ptr<Event> e)
{
	return community_->GetMembersSize() < 10;
}
