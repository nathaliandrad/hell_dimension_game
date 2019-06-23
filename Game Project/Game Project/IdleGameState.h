#pragma once
#include "GameState.h"
#include "Entity.h"
#include <stdlib.h> // for random numbers

class IdleGameState :
	public GameState
{
public:
	float idleTimer; //1 = 1 second
	Entity* entity = NULL;

	IdleGameState();
	~IdleGameState();

	virtual void update(float dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID();

};

