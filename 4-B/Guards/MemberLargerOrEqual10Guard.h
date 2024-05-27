#pragma once

#include "Guard.h"

class MemberLargerOrEqual10Guard : public Guard
{
public:
	MemberLargerOrEqual10Guard(shared_ptr<Community> community);
	~MemberLargerOrEqual10Guard();
	
	bool Condition(shared_ptr<Event> e) override;
private:
	shared_ptr<Community> community_;
};