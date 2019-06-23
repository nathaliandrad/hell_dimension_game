#pragma once
#include "Entity.h"
#include "GameStateMachine.h"
#include "IdleGameState.h"
#include "ChaseGameState.h"
#include "Animation.h"

class Chaser :
	public Entity
{
public:
	GameStateMachine gsm;
	Entity* target = NULL;
	Animation* animation;
	//to change chaser facing direction
	bool faceRightChaser;
	SDL_Rect hitbox;
	Chaser();
	~Chaser();
	
	virtual void update(float dt);
	virtual void draw();

};

