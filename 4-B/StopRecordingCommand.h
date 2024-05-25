#pragma once

#include "Command.h"

class Member;
class Recording;
class StopRecordingCommand : public Command
{
public:
	StopRecordingCommand(shared_ptr<Recording> recording, shared_ptr<Community> community);
	~StopRecordingCommand();

	bool CheckPermission(shared_ptr<Member> member) override;
	void Execute() override;

private:
	shared_ptr<Recording> recording_;
	shared_ptr<Community> community_;
};