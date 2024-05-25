#include "stdafx.h"
#include "Member.h"
#include "Speak.h"
#include "Broadcast.h"

Broadcast::Broadcast()
	:state_(Idle)
{
}

Broadcast::~Broadcast()
{
}

bool Broadcast::GoBroadcast(string id)
{
	if (state_ != Idle) {
		if (speakerId_ == id) {
			if (speakerId_ == "bot") {
				cout << "🤖 go broadcasting...\n";
			}
			else {
				cout << "📢 " << speakerId_ << " is broadcasting...\n";
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		speakerId_ = id;
		state_ = Broadcasting;

		if (speakerId_ == "bot") {
			cout << "🤖 go broadcasting...\n";
		}
		else {
			cout << "📢 " << speakerId_ << " is broadcasting...\n";
		}
		return true;
	}
}

void Broadcast::Speaking(string id, shared_ptr<Speak> speak)
{
	if (state_ != Broadcasting) {
		return;
	}

	if (id != speakerId_) {
		return;
	}

	if (speakerId_ == "bot") {
		cout << "🤖 speaking: " << speak->GetContent() << '\n';
	}
	else {
		cout << "📢 " << speakerId_ << ": " << speak->GetContent() << '\n';
	}
}

void Broadcast::StopBroadcast(string id)
{
	if (state_ != Broadcasting) {
		return;
	}

	if (id != speakerId_) {
		return;
	}


	if (speakerId_ != "bot") {
		cout << "📢 " << speakerId_ << " stop broadcasting\n";
	}

	state_ = Idle;
	speakerId_ = "";
}
