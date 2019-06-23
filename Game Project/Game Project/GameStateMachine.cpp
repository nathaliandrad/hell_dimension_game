#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::push(GameState* state){
	gameStates.push_back(state);
	//run state on enter transition function
	gameStates.back()->onEnter();
}
void GameStateMachine::pop(){
	if (!gameStates.empty()){
		//run transition out function
		if (gameStates.back()->onExit()){
			//if it worked, remove this state from the stack
			//delete the memory the pointer is ponting at
			delete gameStates.back();
			//removes pointer from stack
			gameStates.pop_back();
		}
	}
	//if still not empty, then we are returning to an existing state, lets run onEnter again
	if (!gameStates.empty())
		gameStates.back()->onEnter();
}
void GameStateMachine::changeState(GameState* state){
	pop();
	push(state);


}

void GameStateMachine::clearAll(){
	//delete all memory of states from list
	for (GameState* gs : gameStates)
		delete gs;

	//remove pointers from the list
	gameStates.clear();
}

void GameStateMachine::update(float dt){
	if (!gameStates.empty())
		gameStates.back()->update(dt);
}
void GameStateMachine::render(){
	if (!gameStates.empty())
		gameStates.back()->render();
}


