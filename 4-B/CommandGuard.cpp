#include "stdafx.h"
#include "Guard.h"
#include "Event.h"
#include "utility.h"
#include "Community.h"
#include "Robot.h"
#include "Member.h"
#include "Command.h"
#include "CommandGuard.h"

CommandGuard::CommandGuard(shared_ptr<Command> command, shared_ptr<Community> community, shared_ptr<Robot> robot)
	:command_(command)
	,community_(community)
	,robot_(robot)
{
}

CommandGuard::~CommandGuard()
{
}

bool CommandGuard::Condition(shared_ptr<Event> e)
{
	if (shared_ptr<NewMessageEvent> msgEvent = dynamic_pointer_cast<NewMessageEvent>(e)) {
		if (command_->GetName() != msgEvent->content_) {
			return false;
		}
		
		if (!HasTag(msgEvent->tags_, "bot")) {
			return false;
		}

		shared_ptr<Member> member = community_->GetMember(msgEvent->authorId_);
		if (!member) {
			return false;
		}

		if (!command_->CheckPermission(member)) {
			return false;
		}

		if (robot_->GetQuota() < command_->GetQuota()) {
			return false;
		}

		return true;
	}
	return false;
}