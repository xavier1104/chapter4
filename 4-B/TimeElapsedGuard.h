#pragma once

#include "Guard.h"

class StateSystem;
class TimeElapsedGuard : public Guard
{
public:
	TimeElapsedGuard(int seconds);
	~TimeElapsedGuard();

	bool Condition(shared_ptr<Event> e) override;

private:
	int targetSeconds_;
	int elapsedSeconds_;
};