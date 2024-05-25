#pragma once

#include "Command.h"

class Member;
class Robot;
class PlayAgainCommand : public Command
{
public:
	PlayAgainCommand(shared_ptr<Robot> robot);
	~PlayAgainCommand();

	void Execute() override;

private:
	shared_ptr<Robot> robot_;
};