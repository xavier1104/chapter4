#pragma once

#include "Logger.h"

class Logger;
class Layout
{
public:
	Layout();
	~Layout();

	virtual string Output(string msg, shared_ptr<Logger> logger, Logger::LEVEL level) = 0;
};