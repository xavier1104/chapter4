#pragma once

#include "Command.h"

class KingStopCommand : public Command
{
public:
	KingStopCommand();
	~KingStopCommand();

	bool CheckPermission(shared_ptr<Member> member) override;
};