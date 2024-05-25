#pragma once

#include "stdafx.h"

enum EventType
{
	eET_None = 0,
	eET_Started,
	eET_Login,
	eET_Logout,
	eET_TimeElapsed,
	eET_NewMessage,
	eET_NewPost,
	eET_GoBroadcasting,
	eET_Speak,
	eET_StopBroadcasting,
	eET_QuestionFinished,
	eET_ThanksFinished,
	eET_StopRecording,
	eET_End
};

struct Event
{
	virtual ~Event() = default;
	EventType type_ = eET_None;
};

struct StartedEvent : public Event
{
	StartedEvent()
	{
		type_ = eET_Login;
	}
	chrono::sys_time<chrono::seconds> tp_;
};

struct LoginEvent : public Event
{
	LoginEvent() {
		type_ = eET_Login;
		isAdmin_ = false;
	}
	string userId_;
	bool isAdmin_;
};

struct LogoutEvent : public Event
{
	LogoutEvent() {
		type_ = eET_Logout;
	}
	string userId_;
};

struct NewMessageEvent : public Event
{
	NewMessageEvent() {
		type_ = eET_NewMessage;
	}

	string authorId_;
	string content_;
	vector<string> tags_;
};

struct NewPostEvent : public Event
{
	NewPostEvent() {
		type_ = eET_NewPost;
	}
	string id_;
	string authorId_;
	string title_;
	string content_;
	vector<string> tags_;
};

struct TimeElapsedEvent : public Event
{
	enum TimeUnit
	{
		Second = 0,
		Minute,
		Hour
	};

	TimeElapsedEvent() {
		type_ = eET_TimeElapsed;
		time_ = 0;
		unit_ = Second;
	}

	string GetUnitStr() {
		string unitStr;
		switch (unit_)
		{
		case Second:
		{
			unitStr = "seconds";
			break;
		}
		case Minute:
		{
			unitStr = "minutes";
			break;
		}
		case Hour:
		{
			unitStr = "hours";
			break;
		}
		}
		
		return unitStr;
	}

	int GetSeconds() {
		int seconds = 0;
		switch (unit_)
		{
		case TimeElapsedEvent::Hour:
		{
			seconds = time_ * 3600;
			break;
		}
		case TimeElapsedEvent::Minute:
		{
			seconds = time_ * 60;
			break;
		}
		case TimeElapsedEvent::Second:
		{
			seconds = time_;
			break;
		}
		}

		return seconds;
	}

	int time_;
	TimeUnit unit_;
};

struct GoBroadcastingEvent : public Event
{
	GoBroadcastingEvent() {
		type_ = eET_GoBroadcasting;
	}
	string speakerId_;
};

struct SpeakEvent : public Event
{
	SpeakEvent() {
		type_ = eET_Speak;
	}
	string speakerId_;
	string content_;
};

struct StopBroadcastingEvent : public Event
{
	StopBroadcastingEvent() {
		type_ = eET_StopBroadcasting;
	}
	string speakerId_;
};

struct QuestionFinishedEvent : public Event
{
	QuestionFinishedEvent() {
		type_ = eET_QuestionFinished;
	}

	string winnerId_;
};

struct ThanksFinishedEvent : public Event
{
	ThanksFinishedEvent() {
		type_ = eET_ThanksFinished;
	}
};

struct StopRecordingEvent : public Event
{
	StopRecordingEvent() {
		type_ = eET_StopRecording;
	}
};

struct EndEvent : public Event
{

};