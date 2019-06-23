#pragma once
#include "GameState.h"
#include "Entity.h"
#include <math.h>

class ChaseGameState :
	public GameState
{
public:
	Entity* entity = NULL;
	Entity* target = NULL;//who to chase down

	ChaseGameState();
	~ChaseGameState();

	virtual void update(float dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual std::string getStateID();

};

