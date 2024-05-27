#pragma once

#include "Command.h"

class Member;
class Robot;
class RecordCommand : public Command
{
public:
	RecordCommand();
	~RecordCommand();

	void Execute() override;

};