#include "stdafx.h"
#include "Logger.h"
#include "Exporter.h"
#include "ConsoleExporter.h"
#include "FileExporter.h"
#include "CompositeExporter.h"
#include "Layout.h"
#include "StandardLayout.h"
#include "LoggerParser.h"

extern map<string, shared_ptr<Logger>> Loggers;

void LoggerParser::Parse(string filename)
{
	ifstream f(filename);
	if (f.fail()) {
		cerr << filename << " open failed\n";
		cin.get();
		exit(0);
	}

	string jsonStr((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));
	
	Document doc;
	doc.Parse(jsonStr.c_str());

	if (doc.HasParseError()) {
		cerr << "Parse error:" << GetParseErrorFunc(doc.GetParseError()) << '\n';
		cin.get();
		exit(0);
	}

	static vector<string> names = { "loggers", "app.game", "app.game.ai" };
	Value& parentJson = doc["loggers"];
	shared_ptr<Logger> parent = nullptr;
	shared_ptr<Logger> logger = nullptr;
	for (size_t i = 0; i < names.size(); ++i) {
		if (i == 0) {
			logger = ParseLogger(parentJson, "Root", parent);
		}
		else {
			parentJson = parentJson[names[i].c_str()];
			logger = ParseLogger(parentJson, names[i], parent);
		}

		Loggers.emplace(logger->GetName(), logger);
		parent = logger;
	}
}

shared_ptr<Logger> LoggerParser::ParseLogger(const Value& value, string name, shared_ptr<Logger> parent)
{
	Logger::LEVEL level = Logger::NONE;
	if (value.HasMember("levelThreshold")) {
		string levelStr = value["levelThreshold"].GetString();
		level = Logger::GetLevelByStr(levelStr);
	}

	shared_ptr<Exporter> exporter = nullptr;
	if (value.HasMember("exporter")) {
		exporter = ParseExporter(value["exporter"]);
	}

	shared_ptr<Layout> layout = nullptr;
	if (value.HasMember("layout")) {
		string layoutStr = value["layout"].GetString();
		if (layoutStr == "standard") {
			layout = make_shared<StandardLayout>();
		}
	}
	
	return make_shared<Logger>(name, level, parent, layout, exporter);
}

shared_ptr<Exporter> LoggerParser::ParseExporter(const Value& value)
{
	string type = value["type"].GetString();
	if (type == "console") {
		return make_shared<ConsoleExporter>();
	}
	else if (type == "file") {
		string filename = value["fileName"].GetString();
		return make_shared<FileExporter>(filename);
	}
	else if (type == "composite") {
		vector<shared_ptr<Exporter>> exporters;
		const Value& exporterChildren = value["children"];
		for (SizeType i = 0; i < exporterChildren.Size(); ++i) {
			shared_ptr<Exporter> exporter = ParseExporter(exporterChildren[i]);
			exporters.emplace_back(exporter);
		}
		
		return make_shared<CompositeExporter>(exporters);
	}

	return nullptr;
}

