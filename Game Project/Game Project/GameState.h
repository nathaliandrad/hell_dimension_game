#pragma once
#include <string>
#include "Globals.h"

class GameState
{
public:
	//whether this state is complete or not
	bool done = false;

	GameState();
	~GameState();
	//abstract classes
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() = 0;
	
};

