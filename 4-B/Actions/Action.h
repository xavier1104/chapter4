#pragma once

class Action
{
public:
	Action();
	~Action();
	
	virtual void Do() = 0;
};