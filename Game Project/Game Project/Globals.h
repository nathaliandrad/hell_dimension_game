#pragma once
#include <SDL.h>

class Globals
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Rect camera;
	static int screenWidth, screenHeight;


};

