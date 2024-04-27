#include "stdafx.h"
#include "Layout.h"
#include "Logger.h"
#include "StandardLayout.h"

StandardLayout::StandardLayout()
{
}

StandardLayout::~StandardLayout()
{
}

string StandardLayout::Output(string msg, shared_ptr<Logger> logger, Logger::LEVEL level)
{
	auto now = chrono::system_clock::now();
	auto now_time = chrono::system_clock::to_time_t(now);
	auto now_ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;

	tm timeinfo;
	localtime_s(&timeinfo, &now_time);

	stringstream ss;
	ss << put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
	ss << '.' << std::setfill('0') << std::setw(3) << now_ms.count();

	ss << " |-" << logger->GetLevelStr(level) << ' ' << logger->GetName() << " - " << msg;
	return ss.str();
}
