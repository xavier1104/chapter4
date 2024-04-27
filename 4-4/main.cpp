#include "stdafx.h"
#include "Logger.h"
#include "Layout.h"
#include "Exporter.h"
#include "StandardLayout.h"
#include "ConsoleExporter.h"
#include "CompositeExporter.h"
#include "FileExporter.h"
#include "Game.h"

map<string, shared_ptr<Logger>> Loggers;

int main() {
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

	shared_ptr<Game> game = make_shared<Game>();
	game->Start();

	cin.get();
	return 0;
}