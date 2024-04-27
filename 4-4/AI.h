#pragma once


class Logger;
class AI
{
public:
	AI(string name);
	~AI();
	
	string GetName() { return name_; }
	void MakeDecision();
private:
	string name_;
	shared_ptr<Logger> log_;
};