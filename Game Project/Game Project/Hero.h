#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Bullet.h"
#include <stdlib.h>
#include "SoundManager.h"
#include <iostream>

class Hero : public Entity
{
private:
	Animation* animation;
	bool faceRight;

public:
	Hero();
	~Hero();
	bool invincible = false;
	bool timeoutActive = false;
	float invincibleTimer = 1;

	void setAnimation(Animation* animation);
	SDL_Rect hitbox;
	void beginTimeOut();
	void shoot();
	//special shoot, shoots everywhere
	//void bomb();

	//when hero dies
	void died();
	//score and health of hero
	int score;
	int health;

	//override
	virtual void update(float dt);
	virtual void draw();

	
};

