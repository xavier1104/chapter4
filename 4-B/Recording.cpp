#include "stdafx.h"
#include "Event.h"
#include "Robot.h"
#include "Recording.h"

Recording::Recording(shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:State(robot, system)
{
}

Recording::~Recording()
{
}

void Recording::HandleEvent(shared_ptr<Event> e)
{
	if (shared_ptr<SpeakEvent> speak = dynamic_pointer_cast<SpeakEvent>(e)) {
		records_.emplace_back(speak->content_);
	}
	else if (shared_ptr<StopBroadcastingEvent> stopBroadcasting = dynamic_pointer_cast<StopBroadcastingEvent>(e)) {
		Replay();
	}
	else if (shared_ptr<StopRecordingEvent> stopRecording = dynamic_pointer_cast<StopRecordingEvent>(e)) {
		Replay();
	}
	State::HandleEvent(e);
}

void Recording::Enter(shared_ptr<Event> e)
{
	records_.clear();
	recorderId_ = "";
	if (shared_ptr<GoBroadcastingEvent> goBroadcasting = dynamic_pointer_cast<GoBroadcastingEvent>(e)) {
		recorderId_ = goBroadcasting->speakerId_;
	}
	State::Enter(e);
}

void Recording::Replay()
{
	string msg = "[Record Replay]";
	for (auto&& it = records_.begin(); it != records_.end(); ++it) {
		msg += *it;
		if (next(it) != records_.end()) {
			msg += '\n';
		}
	}
	robot_->Chatting(msg, { recorderId_ });
}
