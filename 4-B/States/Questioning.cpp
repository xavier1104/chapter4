#include "../stdafx.h"
#include "State.h"
#include "../Event.h"
#include "../utility.h"
#include "../Community.h"
#include "../Robot.h"
#include "Questioning.h"

vector<pair<string, string>> Questioning::questions_ = {
	{
		R"(請問哪個 SQL 語句用於選擇所有的行？
A) SELECT *
B) SELECT ALL
C) SELECT ROWS
D) SELECT DATA)", 
		"A"
	},
	{
		R"(請問哪個 CSS 屬性可用於設置文字的顏色？
A) text-align
B) font-size
C) color
D) padding)", 
		"C"
	},
	{
		R"(請問在計算機科學中，「XML」代表什麼？
A) Extensible Markup Language
B) Extensible Modeling Language
C) Extended Markup Language
D) Extended Modeling Language)",
		"A"
	}
};

Questioning::Questioning(shared_ptr<Community> community, shared_ptr<Robot> robot, shared_ptr<StateSystem> system)
	:State(robot, system)
	,idx_(0)
	,community_(community)
{
}

Questioning::~Questioning()
{
}

void Questioning::HandleEvent(shared_ptr<Event> e)
{
	if (shared_ptr<NewMessageEvent> msgEvent = dynamic_pointer_cast<NewMessageEvent>(e)) {
		auto&& [question, ans] = questions_.at(idx_);
		if (ans == msgEvent->content_ && HasTag(msgEvent->tags_, "bot")) {
			robot_->Chatting("Congrats! you got the answer!", { msgEvent->authorId_ });
			scores_[msgEvent->authorId_]++;
			idx_++;
			if (idx_ == questions_.size()) {
				shared_ptr<QuestionFinishedEvent> questionFinished = make_shared<QuestionFinishedEvent>();
				questionFinished->winnerId_ = GetWinnerId();
				community_->HandleEvent(questionFinished);
			}
			else {
				robot_->Chatting(to_string(idx_) + ". " + questions_[idx_].first);
			}
		}
	}

	State::HandleEvent(e);
}

void Questioning::Enter(shared_ptr<Event> e)
{
	idx_ = 0;
	scores_.clear();
	robot_->Chatting("KnowledgeKing is started!");
	robot_->Chatting(to_string(idx_) + ". " + questions_[idx_].first);
	State::Enter(e);
}

string Questioning::GetWinnerId()
{
	string winner;
	int maxScore = -1;
	for (auto&& [id, score] : scores_) {
		if (score > maxScore) {
			winner = id;
			maxScore = score;
		}
	}

	return winner;
}