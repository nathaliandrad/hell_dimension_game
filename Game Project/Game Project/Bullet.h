#pragma once
#include "Entity.h"
#include <cmath>
class Bullet :
	public Entity
{
public:
	Bullet();
	~Bullet();

	float angle;
	float movementSpeed;

	void update(float dt);
	void draw();
	//hitbox for colision purpose
	SDL_Rect hitbox;

};

