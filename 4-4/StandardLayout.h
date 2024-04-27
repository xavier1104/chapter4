#pragma once

class StandardLayout : Layout
{
public:
	StandardLayout();
	~StandardLayout();

	string Output(string msg, shared_ptr<Logger> logger) override;
};