#include "stdafx.h"
#include "Event.h"
#include "Community.h"
#include "Robot.h"
#include "Broadcast.h"
#include "ChatRoom.h"
#include "Forum.h"
#include "DataType.h"
#include "RobotFSMFacade.h"
#include "GuardArgs.h"
#include "ActionArgs.h"

EventType ParseEventType(string& eventName)
{
	if (eventName == "started") {
		return eET_Started;
	}
	else if (eventName == "login") {
		return eET_Login;
	}
	else if (eventName == "logout") {
		return eET_Logout;
	}
	else if (eventName == "new message") {
		return eET_NewMessage;
	}
	else if (eventName == "new post") {
		return eET_NewPost;
	}
	else if (eventName == "go broadcasting") {
		return eET_GoBroadcasting;
	}
	else if (eventName == "speak") {
		return eET_Speak;
	}
	else if (eventName == "stop broadcasting") {
		return eET_StopBroadcasting;
	}
	else if (eventName == "end") {
		return eET_End;
	}
	else if (eventName.find("elapsed")) {
		return eET_TimeElapsed;
	}
	
	cerr << "Event type not found\n";
	cin.get();
	exit(0);

	return eET_None;
}

bool ParseLine(string line, string& eventHeader, shared_ptr<Event>& eventArgs)
{
	size_t left = line.find('[');
	size_t right = line.find(']');
	eventHeader = line.substr(left + 1, right - left - 1);
	EventType eventType = ParseEventType(eventHeader);
	
	left = line.find('{');
	right = line.find('}');

	Document doc;
	if (left != string::npos && right != string::npos) {
		string jsonStr = line.substr(left, right - left + 1);
		doc.Parse(jsonStr.c_str());
		if (doc.HasParseError()) {
			cerr << "Parse error:" << GetParseErrorFunc(doc.GetParseError()) << '\n';
			cin.get();
			exit(0);
		}
	}

	switch (eventType) 
	{
	case eET_Started:
	{
		if (!doc.HasMember("time")) {
			break;
		}
		Value& time = doc["time"];
		string timeStr = time.GetString();

		istringstream ss(timeStr);
		shared_ptr<StartedEvent> startedEvent = make_shared<StartedEvent>();
		ss >> chrono::parse("%Y-%m-%d %H:%M:%S", startedEvent->tp_);

		if (ss.fail()) {
			cerr << "Failed parse time string\n";
			cin.get();
			exit(0);
		}

		eventArgs = startedEvent;
		return true;
	}
	case eET_Login:
	{
		if (!doc.HasMember("userId")) {
			break;
		}

		if (!doc.HasMember("isAdmin")) {
			break;
		}

		Value& userId = doc["userId"];
		Value& isAdmin = doc["isAdmin"];

		shared_ptr<LoginEvent> loginEvent = make_shared<LoginEvent>();
		loginEvent->userId_ = userId.GetString();
		loginEvent->isAdmin_ = isAdmin.GetBool();
		
		eventArgs = loginEvent;
		return true;
	}
	case eET_Logout:
	{
		if (!doc.HasMember("userId")) {
			break;
		}

		Value& userId = doc["userId"];

		shared_ptr<LogoutEvent> logoutEvent = make_shared<LogoutEvent>();
		logoutEvent->userId_ = userId.GetString();
		eventArgs = logoutEvent;
		return true;
	}
	case eET_TimeElapsed:
	{
		vector<string> tokens;
		stringstream ss(eventHeader);
		string token;
		while (getline(ss, token, ' ')) {
			tokens.emplace_back(token);
		}

		if (tokens.size() < 2) {
			break;
		}

		shared_ptr<TimeElapsedEvent> timeEvent = make_shared<TimeElapsedEvent>();
		timeEvent->time_ = stoi(tokens[0]);
		string unit = tokens[1];
		if (unit == "seconds") {
			timeEvent->unit_ = TimeElapsedEvent::Second;
		}
		else if (unit == "minutes") {
			timeEvent->unit_ = TimeElapsedEvent::Minute;
		}
		else if (unit == "hours") {
			timeEvent->unit_ = TimeElapsedEvent::Hour;
		}

		eventArgs = timeEvent;
		return true;
	}
	case eET_NewMessage:
	{
		if (!doc.HasMember("authorId") || !doc.HasMember("content") || !doc.HasMember("tags")) {
			break;
		}

		Value& authorId = doc["authorId"];
		Value& content = doc["content"];
		Value& tags = doc["tags"];

		shared_ptr<NewMessageEvent> newMessageEvent = make_shared<NewMessageEvent>();
		newMessageEvent->authorId_ = authorId.GetString();
		newMessageEvent->content_ = content.GetString();
		for (SizeType i = 0; i < tags.GetArray().Size(); ++i) {
			newMessageEvent->tags_.emplace_back(tags[i].GetString());
		}

		eventArgs = newMessageEvent;
		return true;
	}
	case eET_NewPost:
	{
		if (!doc.HasMember("id") || !doc.HasMember("authorId") || !doc.HasMember("title")
			|| !doc.HasMember("content") || !doc.HasMember("tags")) {
			break;
		}

		Value& id = doc["id"];
		Value& authorId = doc["authorId"];
		Value& title = doc["title"];
		Value& content = doc["content"];
		Value& tags = doc["tags"];

		shared_ptr<NewPostEvent> postEvent = make_shared<NewPostEvent>();
		postEvent->id_ = id.GetString();
		postEvent->authorId_ = authorId.GetString();
		postEvent->title_ = title.GetString();
		postEvent->content_ = content.GetString();
		for (SizeType i = 0; i < tags.GetArray().Size(); ++i) {
			postEvent->tags_.emplace_back(tags[i].GetString());
		}
		eventArgs = postEvent;
		return true;
	}
	case eET_GoBroadcasting:
	{
		if (!doc.HasMember("speakerId")) {
			break;
		}

		Value& speakId = doc["speakerId"];
		shared_ptr<GoBroadcastingEvent> goBroadcastingEvent = make_shared<GoBroadcastingEvent>();
		goBroadcastingEvent->speakerId_ = speakId.GetString();
		eventArgs = goBroadcastingEvent;
		return true;
	}
	case eET_Speak:
	{
		if (!doc.HasMember("speakerId") || !doc.HasMember("content")) {
			break;
		}

		Value& speakId = doc["speakerId"];
		Value& content = doc["content"];
		shared_ptr<SpeakEvent> speakEvent = make_shared<SpeakEvent>();
		speakEvent->speakerId_ = speakId.GetString();
		speakEvent->content_ = content.GetString();
		eventArgs = speakEvent;
		return true;
	}
	case eET_StopBroadcasting:
	{
		if (!doc.HasMember("speakerId")) {
			break;
		}

		Value& speakId = doc["speakerId"];
		shared_ptr<StopBroadcastingEvent> stopBroadcastingEvent = make_shared<StopBroadcastingEvent>();
		stopBroadcastingEvent->speakerId_ = speakId.GetString();
		eventArgs = stopBroadcastingEvent;
		return true;
	}
	case eET_End:
	{
		shared_ptr<EndEvent> endEvent = make_shared<EndEvent>();
		eventArgs = endEvent;
		return true;
	}
	}

	return false;
}

void Parse(string filename, vector<shared_ptr<Event>>& events)
{
	events.clear();

	ifstream f(filename);
	if (f.fail()) {
		cerr << filename << " open failed\n";
		return;
	}

	string line;
	string eventHeader;
	shared_ptr<Event> e;
	while (!f.eof()) {
		getline(f, line);
		if (!ParseLine(line, eventHeader, e)) {
			continue;
		}
		events.emplace_back(e);
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	vector<shared_ptr<Event>> events;
	//Parse("interaction.chit-chat.in", events);
	//Parse("knowledge-king.normal-play.in", events);
	//Parse("knowledge-king.stop.in", events);
	//Parse("normal.chit-chat.in", events);
	//Parse("quota.in", events);
	Parse("recording.normal.in", events);

	// basic objects
	shared_ptr<Broadcast> broadcast = make_shared<Broadcast>();
	shared_ptr<ChatRoom> chatroom = make_shared<ChatRoom>();
	shared_ptr<Forum> forum = make_shared<Forum>();
	shared_ptr<Robot> robot = make_shared<Robot>(broadcast, chatroom, forum);
	shared_ptr<Community> community = make_shared<Community>(robot, broadcast, chatroom, forum);
	
	shared_ptr<RobotFSMFacade> robotFSMFacade = make_shared<RobotFSMFacade>(robot, community, broadcast);

	robotFSMFacade->CreateRootFSM(
		eS_Normal,
		{ 
			make_shared<STransition>(eS_Normal, eET_NewMessage, make_shared<SCommandGuard>(eC_King), make_shared<SCommandAction>(eC_King), eS_KnowledgeKing),
			make_shared<STransition>(eS_KnowledgeKing, eET_ThanksFinished, nullptr, nullptr, eS_Normal),
			make_shared<STransition>(eS_KnowledgeKing, eET_NewMessage, make_shared<SCommandGuard>(eC_KingStop), make_shared<SCommandAction>(eC_KingStop), eS_Normal),
			make_shared<STransition>(eS_Normal, eET_NewMessage, make_shared<SCommandGuard>(eC_Record), make_shared<SCommandAction>(eC_Record), eS_Record),
			make_shared<STransition>(eS_Record, eET_NewMessage, make_shared<SCommandGuard>(eC_StopRecording), make_shared<SCommandAction>(eC_StopRecording), eS_Normal)
		});

	robotFSMFacade->CreateNodeFSM(
		eS_Normal,
		eS_DefaultConversation,
		{
			make_shared<STransition>(eS_DefaultConversation, eET_Login, make_shared<SMemberLargerOrEqual10Guard>(), nullptr, eS_Interacting),
			make_shared<STransition>(eS_Interacting, eET_Logout, make_shared<SMemberLessThan10Guard>(), nullptr, eS_DefaultConversation)
		});
	
	robotFSMFacade->CreateNodeFSM(
		eS_Record,
		eS_Waiting,
		{
			make_shared<STransition>(eS_Waiting, eET_GoBroadcasting, nullptr, nullptr, eS_Recording),
			make_shared<STransition>(eS_Recording, eET_StopBroadcasting, nullptr, nullptr, eS_Waiting)
		}
	);

	robotFSMFacade->CreateNodeFSM(
		eS_KnowledgeKing,
		eS_Questioning,
		{
			make_shared<STransition>(eS_Questioning, eET_TimeElapsed, make_shared<STimeElapsedGuard>(3600), nullptr, eS_ThanksForJoining),
			make_shared<STransition>(eS_Questioning, eET_QuestionFinished, nullptr, nullptr, eS_ThanksForJoining),
			make_shared<STransition>(eS_ThanksForJoining, eET_NewMessage, make_shared<SCommandGuard>(eC_PlayAgain), make_shared<SCommandAction>(eC_PlayAgain), eS_Questioning)
		}
	);

	robotFSMFacade->Finish();

	for (auto& e : events) {
		community->HandleEvent(e);
	}
	
	cin.get();
	return 0;
}