#ifndef MAIN_H
#define MAIN_H
#include "game.h"

class Main
{
public:
	Main();
	~Main();

	void Start();
	void Stop();

private:
	bool m_isRunning;
	Game m_game;
	void Run();
};

#endif