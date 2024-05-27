#include "../stdafx.h"
#include "../Event.h"
#include "TimeElapsedGuard.h"

TimeElapsedGuard::TimeElapsedGuard(int seconds)
	:elapsedSeconds_(0)
	, targetSeconds_(seconds)
{
}

TimeElapsedGuard::~TimeElapsedGuard()
{
}

bool TimeElapsedGuard::Condition(shared_ptr<Event> e)
{
	if (shared_ptr<TimeElapsedEvent> timeEvent = dynamic_pointer_cast<TimeElapsedEvent>(e)) {
		elapsedSeconds_ += timeEvent->GetSeconds();
		if (elapsedSeconds_ < targetSeconds_) {
			return false;
		}

		return true;
	}

	return false;
}
