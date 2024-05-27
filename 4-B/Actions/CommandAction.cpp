#include "../stdafx.h"
#include "../Commands/Command.h"
#include "../Robot.h"
#include "CommandAction.h"

CommandAction::CommandAction(shared_ptr<Command> command, shared_ptr<Robot> robot)
	:command_(command)
	,robot_(robot)
{
}

CommandAction::~CommandAction()
{
}

void CommandAction::Do()
{
	robot_->CostQuota(command_->GetQuota());
	command_->Execute();
}
