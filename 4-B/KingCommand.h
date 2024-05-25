#pragma once

#include "Command.h"

class KingCommand : public Command
{
public:
	KingCommand();

	~KingCommand();

	bool CheckPermission(shared_ptr<Member> member) override;
};