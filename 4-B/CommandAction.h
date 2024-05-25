#pragma once

#include "Action.h"

class CommandAction : public Action
{
public:
	CommandAction(shared_ptr<Command> command, shared_ptr<Robot> robot);
	~CommandAction();

	void Do() override;
	
private:
	shared_ptr<Command> command_;
	shared_ptr<Robot> robot_;
};