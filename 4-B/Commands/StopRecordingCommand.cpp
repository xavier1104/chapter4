#include "../stdafx.h"
#include "../States/Recording.h"
#include "../Member.h"
#include "../Event.h"
#include "../Community.h"
#include "StopRecordingCommand.h"

StopRecordingCommand::StopRecordingCommand(shared_ptr<Recording> recording, shared_ptr<Community> community)
	:Command(0, "stop-recording")
	,recording_(recording)
	,community_(community)
{
}

StopRecordingCommand::~StopRecordingCommand()
{
}

bool StopRecordingCommand::CheckPermission(shared_ptr<Member> member)
{
	return recording_->GetRecorderId() == member->GetID();
}

void StopRecordingCommand::Execute()
{
	shared_ptr<StopRecordingEvent> e = make_shared<StopRecordingEvent>();
	community_->HandleEvent(e);
}
