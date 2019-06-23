#include "Chaser.h"


Chaser::Chaser()
{
	type = "chaser";
	IdleGameState* idle = new IdleGameState();
	idle->entity = this;
	faceRightChaser = true;
	hitbox.w = 36;
	hitbox.h = 56;
	gsm.push(idle);
}


Chaser::~Chaser()
{
}

void Chaser::update(float dt){
	gsm.update(dt);
	GameState* currentState = gsm.gameStates.back();

	if (velocity.x > 0){
		faceRightChaser = true;
	
	}
	if (velocity.x < 0){
		faceRightChaser = false;

	}


	if (currentState->done){
		if (currentState->getStateID() == "idleState"){
			//add chase state to the top of the stack
			ChaseGameState* newState = new ChaseGameState();
			newState->entity = this;
			newState->target = target;

			gsm.push(newState);
		}
		else if (currentState->getStateID() == "chaseState"){
			//assuming this state is never on bottom, we will just kill it
			gsm.pop();
		}
	}

	updateMovement(dt); 
	//updating hitbox
	hitbox.x = position.x + 15;
	hitbox.y = position.y + 5;
	
	animation->update(dt);
}
void Chaser::draw(){

	gsm.render();

	SDL_SetRenderDrawColor(renderer, 6, 16, 54, 1);
	SDL_Rect hitboxCam = { hitbox.x , hitbox.y , hitbox.w, hitbox.h };
	SDL_RenderFillRect(renderer, &hitboxCam);
	


	if (animation != NULL){

		if (faceRightChaser){
			animation->draw(position.x , position.y);

		}
		else{
			animation->draw(position.x, position.y , true);

		}
	}


}
