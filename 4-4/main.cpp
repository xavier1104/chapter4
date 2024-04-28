#include "stdafx.h"
#include "Logger.h"
#include "Layout.h"
#include "Exporter.h"
#include "StandardLayout.h"
#include "ConsoleExporter.h"
#include "CompositeExporter.h"
#include "FileExporter.h"
#include "Game.h"
#include "LoggerParser.h"

map<string, shared_ptr<Logger>> Loggers;

void GenLoggers()
{
	shared_ptr<Logger> root = make_shared<Logger>(
		"Root",
		Logger::DEBUG,
		nullptr,
		make_shared<StandardLayout>(),
		make_shared<ConsoleExporter>()
	);

	shared_ptr<Logger> gameLogger = make_shared<Logger>(
		"app.game",
		Logger::INFO,
		root,
		nullptr,
		make_shared<CompositeExporter>(
			vector<shared_ptr<Exporter>>{
				make_shared<ConsoleExporter>(),
				make_shared<CompositeExporter>(
					vector<shared_ptr<Exporter>>
					{
						make_shared<FileExporter>("game.log"),
						make_shared<FileExporter>("game.backup.log")
					}
				)}
		)
	);

	shared_ptr<Logger> aiLogger = make_shared<Logger>(
		"app.game.ai",
		Logger::TRACE,
		gameLogger,
		make_shared<StandardLayout>(),
		nullptr
	);

	Loggers.emplace(root->GetName(), root);
	Loggers.emplace(gameLogger->GetName(), gameLogger);
	Loggers.emplace(aiLogger->GetName(), aiLogger);
}

int main() {
	remove("game.log");
	remove("game.backup.log");

	cout << "enter 0(run), 1(read json) : ";
	char choice = '0';
	cin >> choice;
	cin.ignore();

	switch (choice)
	{
	case '0':
		GenLoggers();
		break;
	case '1':
		LoggerParser::Parse("loggers.json");
		break;
	default:
		cerr << "error!\n";
		cin.get();
		exit(0);
		break;
	}

	shared_ptr<Game> game = make_shared<Game>();
	game->Start();

	cin.get();
	return 0;
}