#include "stdafx.h"
#include "Member.h"
#include "KingCommand.h"

KingCommand::KingCommand()
	:Command(5, "king")
{
}

KingCommand::~KingCommand()
{
}

bool KingCommand::CheckPermission(shared_ptr<Member> member)
{
	return member->GetPermission() == Member::Admin;
}
