#include "../stdafx.h"
#include "../Event.h"
#include "StateSystem.h"
#include "../Robot.h"
#include "State.h"

State::State(shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:system_(system)
	,robot_(robot)
{
}

State::~State()
{
}

void State::HandleEvent(shared_ptr<Event> e)
{
	if (!system_) {
		return;
	}
	system_->HandleEvent(e);
}

void State::Exit(shared_ptr<Event> e)
{
	if (!system_) {
		return;
	}
	
	system_->Exit(e);
}

void State::Enter(shared_ptr<Event> e)
{
	if (!system_) {
		return;
	}
	
	system_->Enter(e);
}
