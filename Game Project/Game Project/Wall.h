#pragma once
#include "Entity.h"
#include "Animation.h"
class Wall : public Entity
{
private:
	float w, h;

public:
	Wall();
	~Wall();

	void setWH(float w, float y);

	//override
	virtual void draw();
	SDL_Rect hitbox;
	virtual void update(float dt);
};

