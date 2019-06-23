#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;


int main(int argc, char** argv){
	//initialise SDL with all its sub systems e.g video, input, sound etc
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout<<"SDL failed: "<<SDL_GetError()<<endl;
		system("pause");
		return -1;
	}

	//create window to render into
	//params: (title, position x, position y, width, height, window flags)
	SDL_Window* window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN); //fullscreen with last param like this: SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN

	if(window == NULL)
	{
		cout<<"window failed: "<<SDL_GetError()<<endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	//create a renderer, which helps draw stuff to the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(renderer == NULL){
		cout<<"renderer failed: "<<SDL_GetError()<<endl;
		system("pause");
		SDL_Quit(); //cleans up SDL for us
		return -1;
	}

	//set drawing colour for renderer, uses RGBA, each value between 0-255
	SDL_SetRenderDrawColor(renderer, 0, 228, 255,255);
	//clear screen with draw color
	SDL_RenderClear(renderer);

	//rectangle to draw ( x, y, width, height)
	SDL_Rect rectangle = {50, 30,200, 100};
	//magenta
	SDL_SetRenderDrawColor(renderer, 255,0,255,255);

	//draw coloured in rectangle to screen
	SDL_RenderFillRect(renderer, &rectangle);

	//render to the screen
	SDL_RenderPresent(renderer);

	//wait for 5 seconds
	SDL_Delay(5000);//in milliseconds

	//CLEAN UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}