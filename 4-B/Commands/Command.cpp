#include "../stdafx.h"
#include "Command.h"

Command::Command(int quota, string name)
	:quota_(quota)
	,name_(name)
{
}

Command::~Command()
{
}
