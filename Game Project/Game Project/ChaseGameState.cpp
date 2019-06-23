#include "ChaseGameState.h"


ChaseGameState::ChaseGameState()
{
}


ChaseGameState::~ChaseGameState()
{
}

void ChaseGameState::update(float dt){
	if (entity != NULL && target != NULL){
		//distance bewteen entity and target
		float distance = abs(sqrt(pow(entity->position.x - target->position.x, 2) + pow(entity->position.y - target->position.y, 2)));

		if (distance > 10){

			//angle between entity and target
			float angleBetween = atan2(target->position.y - entity->position.y, target->position.x - entity->position.x) ;//in radians
			//velocity of enemy
			entity->velocity.x = 50;
			entity->velocity.y = 0;
			entity->velocity = entity->velocity.setAngle(angleBetween);

		}
		else{
			entity->velocity.x = 0;
			entity->velocity.y = 0;
			
			done = true;
		}
	}
		else {
			done = true;
		}
	
}
void ChaseGameState::render(){

}
bool ChaseGameState::onEnter(){
	return true;
}
bool ChaseGameState::onExit(){
	return true;
}
std::string ChaseGameState::getStateID(){
	return "chaseState";
}



