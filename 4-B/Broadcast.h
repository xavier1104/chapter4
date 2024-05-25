#pragma once

class Member;
class Speak;
class Broadcast
{
public:
	enum BroadcastState
	{
		Idle = 0,
		Broadcasting
	};

public:
	Broadcast();
	~Broadcast();

	bool GoBroadcast(string id);
	void Speaking(string id, shared_ptr<Speak> speak);
	void StopBroadcast(string id);
	BroadcastState GetState() { return state_; }

private:
	BroadcastState state_;
	string speakerId_;
};