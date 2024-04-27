#pragma once

class StandardLayout : public Layout
{
public:
	StandardLayout();
	~StandardLayout();

	string Output(string msg, shared_ptr<Logger> logger, Logger::LEVEL level) override;
};