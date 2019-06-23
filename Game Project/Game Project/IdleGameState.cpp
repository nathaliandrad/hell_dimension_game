#include "IdleGameState.h"
#include "Entity.h"


IdleGameState::IdleGameState()
{
}


IdleGameState::~IdleGameState()
{
}


void IdleGameState::update(float dt){
	idleTimer -= dt;
	if (idleTimer <= 0){
		done = true;
	}
}
void IdleGameState::render(){

}
bool IdleGameState::onEnter(){
	idleTimer = rand() % 20 + 1;//1 - 10 seconds of idle time
	done = false;

	return true;
}
bool IdleGameState::onExit(){
	return true;
}
std::string IdleGameState::getStateID(){
	return "idleState";
}
