#pragma once


class Logger;
class AI;
class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	shared_ptr<Logger> log_;
	vector<shared_ptr<AI>> players_;
};