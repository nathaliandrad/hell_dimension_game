#include "Bullet.h"



Bullet::Bullet()
{
	type = "bullet";
	//hitbox size
	hitbox.w = 20;
	hitbox.h = 8;
}


Bullet::~Bullet()
{
}


void Bullet::update(float dt){
	//convert angle in degrees to radians(for trigonometry)
	float angleInRadians = angle;

	velocity.x = movementSpeed*cos(angleInRadians);
	velocity.y = movementSpeed*sin(angleInRadians);
	//updating hitbox position
	hitbox.x = position.x ;
	hitbox.y = position.y ;

	updateMovement(dt);
}

void Bullet::draw(){

	//actual bullet rectangle
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect hitboxCam = { hitbox.x, hitbox.y, hitbox.w, hitbox.h };
	SDL_RenderFillRect(renderer, &hitboxCam);


}
