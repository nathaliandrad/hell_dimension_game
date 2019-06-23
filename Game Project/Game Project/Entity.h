#pragma once
#include <SDL.h>
#include "Vector.h"
#include <list>
#include "Globals.h"


using namespace std;

class Entity
{
protected:
	SDL_Renderer* renderer;

public:
	Vector position; // x,y representing where it is on the level 
	Vector velocity; // how fast and which direction the thing is moving
	Vector acceleration; //how much to increase/decrease velocity
	string type;

	Entity();
	~Entity();

	void setRenderer(SDL_Renderer* renderer);
	void setXY(float x, float y);
	
	float getX();
	float getY();

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw();

	//statics are shared/global variables
	static list<Entity*> *entities;

};

