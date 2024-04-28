#include "stdafx.h"
#include "Exporter.h"
#include "Layout.h"
#include "Logger.h"

Logger::Logger(string name, LEVEL level, shared_ptr<Logger> parent, shared_ptr<Layout> layout, shared_ptr<Exporter> exporter)
{
	name_ = name;

	if (name == "Root") {
		level_ = level;
		parent_ = nullptr;
		layout_ = layout;
		exporter_ = exporter;
	}
	else {
		if (parent == nullptr) {
			cerr << "Child logger not assign parent logger error!\n";
			cin.get();
			exit(0);
		}

		parent_ = parent;
		level_ = level == NONE ? parent->GetLevel() : level;
		layout_ = layout == nullptr ? parent->GetLayout() : layout;
		exporter_ = exporter == nullptr ? parent->GetExporter() : exporter;
	}
}

Logger::~Logger()
{
}

void Logger::Write(LEVEL level, string content)
{
	if (level_ <= level) {
		string msgFormated = layout_->Output(content, shared_from_this(), level);
		exporter_->Export(msgFormated);
	}
}

string Logger::GetLevelStr(LEVEL level)
{
	switch (level)
	{
	case TRACE: return "TRACE";
	case INFO:	return "INFO";
	case DEBUG:	return "DEBUG";
	case WARN:	return "WARN";
	case ERROR:	return "ERROR";
	}

	return "";
}

Logger::LEVEL Logger::GetLevelByStr(string level)
{
	if (level == "TRACE") {
		return TRACE;
	}
	else if (level == "INFO") {
		return INFO;
	}
	else if (level == "DEBUG") {
		return DEBUG;
	}
	else if (level == "WARN") {
		return WARN;
	}
	else if (level == "ERROR") {
		return ERROR;
	}

	return NONE;
}
