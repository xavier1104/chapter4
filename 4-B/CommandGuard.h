#pragma once

#include "Guard.h"

class Community;
class Robot;
class Command;
class CommandGuard : public Guard
{
public:
	CommandGuard(shared_ptr<Command> command, shared_ptr<Community> community, shared_ptr<Robot> robot);
	~CommandGuard();

	bool Condition(shared_ptr<Event> e) override;

private:
	shared_ptr<Command> command_;
	shared_ptr<Community> community_;
	shared_ptr<Robot> robot_;
};