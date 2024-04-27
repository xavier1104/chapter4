#include "stdafx.h"
#include "AI.h"
#include "Logger.h"
#include "Game.h"

extern map<string, shared_ptr<Logger>> Loggers;

Game::Game()
{
	auto&& it = Loggers.find("app.game");
	if (it == Loggers.end()) {
		cerr << " \"app.game\" Log name not found\n";
		cin.get();
		exit(0);
	}

	log_ = it->second;

	players_.emplace_back(make_shared<AI>("AI 1"));
	players_.emplace_back(make_shared<AI>("AI 2"));
	players_.emplace_back(make_shared<AI>("AI 3"));
	players_.emplace_back(make_shared<AI>("AI 4"));
}

Game::~Game()
{
}

void Game::Start()
{
	log_->Write(Logger::INFO, "The game begins.");
	for (auto& ai : players_) {
		ai->MakeDecision();
	}
	log_->Write(Logger::DEBUG, "Game ends.");
}
