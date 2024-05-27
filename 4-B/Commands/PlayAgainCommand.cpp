#include "../stdafx.h"
#include "Command.h"
#include "../Robot.h"
#include "PlayAgainCommand.h"

PlayAgainCommand::PlayAgainCommand(shared_ptr<Robot> robot)
	:Command(5, "play again")
	,robot_(robot)
{
}

PlayAgainCommand::~PlayAgainCommand()
{
}

void PlayAgainCommand::Execute()
{
	robot_->Chatting("KnowledgeKing is gonna start again!");
}
