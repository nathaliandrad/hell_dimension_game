#include "Wall.h"


Wall::Wall()
{
	type = "wall";
	hitbox.w = 1600;
	hitbox.h = 30;
	

	
}


Wall::~Wall()
{
}


void Wall::setWH(float w, float h){
	this->w = w;
	this->h = h;
}

void Wall::update(float dt){
	hitbox.x = position.x;
	hitbox.y = position.y;

}

void Wall::draw(){


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect hitboxCamTop = { 0, 0, hitbox.w, hitbox.h };
	SDL_RenderFillRect(renderer, &hitboxCamTop);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_Rect hitboxCamBottom = { 0, 770, hitbox.w, hitbox.h };
	SDL_RenderFillRect(renderer, &hitboxCamBottom);


}

