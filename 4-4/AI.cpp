#include "stdafx.h"
#include "Logger.h"
#include "AI.h"

extern map<string, shared_ptr<Logger>> Loggers;

AI::AI(string name)
	:name_(name)
{
	auto&& it = Loggers.find("app.game.ai");
	if (it == Loggers.end()) {
		cerr << " \"app.game\" Log name not found\n";
		cin.get();
		exit(0);
	}

	log_ = it->second;
}

AI::~AI()
{
}

void AI::MakeDecision()
{
	log_->Write(Logger::TRACE, name_ + " starts making decisions...");
	log_->Write(Logger::WARN, name_ + " decides to give up.");
	log_->Write(Logger::ERROR, "Something goes wrong when AI gives up.");
	log_->Write(Logger::TRACE, name_ + " completes its decision.");
}
