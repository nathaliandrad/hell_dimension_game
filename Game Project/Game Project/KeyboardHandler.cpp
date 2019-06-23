#include "KeyboardHandler.h"
#include "Chaser.h"


KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event){
	if (event->type == SDL_KEYDOWN){
		//trigger on R key, but dont do this if repeat event is fired
		if (event->key.keysym.scancode == SDL_SCANCODE_R && event->key.repeat == 0){
			//reset players to starting position
			hero->setXY(400, 400);
			
			
		}
		//SHOOT
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE && event->key.repeat == 0){
			hero->shoot();
			
		}



	}
}
void KeyboardHandler::updateHeldKeys(){
	//get array of all keyboard key states(1=held, 0=not held down)
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	//reset acceleration for hero to nothing
	hero->acceleration.x = 0;
	hero->acceleration.y = 0;

	//check held down keys
	if (keystates[SDL_SCANCODE_UP])
		hero->acceleration.y = -120;
	if (keystates[SDL_SCANCODE_DOWN])
		hero->acceleration.y = 120;
	if (keystates[SDL_SCANCODE_LEFT])
		hero->acceleration.x = -140;
	if (keystates[SDL_SCANCODE_RIGHT])
		hero->acceleration.x = 140;

}


