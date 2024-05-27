#include "../stdafx.h"
#include "../Member.h"
#include "KingStopCommand.h"

KingStopCommand::KingStopCommand()
	:Command(0, "king-stop")
{
}

KingStopCommand::~KingStopCommand()
{
}

bool KingStopCommand::CheckPermission(shared_ptr<Member> member)
{
	return member->GetPermission() == Member::Admin;
}
