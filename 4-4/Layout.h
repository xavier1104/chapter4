#pragma once

class Layout
{
public:
	Layout();
	~Layout();

	virtual string Output(string msg, shared_ptr<Logger> logger) = 0;
};