#pragma once

struct Event;
class Guard
{
public:
	Guard();
	~Guard();

	virtual bool Condition(shared_ptr<Event> e) = 0;
};