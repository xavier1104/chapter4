#pragma once

#include "Guard.h"

class Community;
class MemberLessThan10Guard : public Guard
{
public:
	MemberLessThan10Guard(shared_ptr<Community> community);
	~MemberLessThan10Guard();

	bool Condition(shared_ptr<Event> e) override;

private:
	shared_ptr<Community> community_;
};