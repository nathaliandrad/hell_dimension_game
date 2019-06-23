#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include "Wall.h"
#include <list>
#include "InputHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GameControllerHandler.h"
#include <stdlib.h> 
#include <time.h>
#include "SoundManager.h"
#include "Globals.h"
#include "Chaser.h"
#include <fstream>

using namespace std;



//function to check colision
bool checkColision(SDL_Rect b1, SDL_Rect b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}

//to get a random number for positions of chaser
/*
float LO = -1000;
float HI = 2300;
float randomX = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
float randomY = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
*/
float randomXPosition(){

	float randomNumX = rand() % 2300 + (-1000);
	float numbers = -100;

	return randomNumX;

}

float randomYPosition(){
	float randomNumY = rand() % 1600 + (-800);
	float numbers = 1800;

	return randomNumY;

	
}


int main(int argc, char** argv){
	
	srand(time(NULL));
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout<<"SDL failed: "<<SDL_GetError()<<endl;
		system("pause");
		return -1;
	}

	//need to initialise other sub libraries
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		cout << "sdl image failed: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//INIT sdl ttf
	if (TTF_Init() != 0){
		cout << "sdl ttf failed: " << TTF_GetError() << endl;
		system("pause");
		return -1;
	}
	//INIT sdl mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		cout << "Mixer error: " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create window to render into
	//params: (title, position x, position y, width, height, window flags)
	SDL_Window* window = SDL_CreateWindow("Hell Dimension", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1200, 800, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN); //fullscreen with last param like this: SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN

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
	//tell globals to point to the things we just made
	Globals::window = window;
	Globals::renderer = renderer;


	//uploading spritesheet Image
	//black holes
	SDL_Surface* bloodSurface = IMG_Load("assets/blackBlackHolesss.png");
	SDL_SetColorKey(bloodSurface, 1, SDL_MapRGB(bloodSurface->format, 256, 256, 255));
	SDL_Texture* bloodSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, bloodSurface);
	SDL_FreeSurface(bloodSurface);

	

	//stars
	SDL_Surface* shinySurface = IMG_Load("assets/shiny.png");
	SDL_SetColorKey(shinySurface, 1, SDL_MapRGB(shinySurface->format, 0, 0, 0));
	SDL_Texture* shinySpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, shinySurface);
	SDL_FreeSurface(shinySurface);

	//hero
	SDL_Surface* runSurface = IMG_Load("assets/soldier_shoot_cut.png");
	SDL_SetColorKey(runSurface,1,SDL_MapRGB(runSurface->format,0,0,255)); //rgba(24, 39, 205, 1) (0,0,255)
	SDL_Texture* runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);
	SDL_FreeSurface(runSurface);


	//chaser
	SDL_Surface* demonSurface = IMG_Load("assets/demon_cut.png");
	SDL_SetColorKey(demonSurface, 1, SDL_MapRGB(demonSurface->format, 0, 0, 255)); 
	SDL_Texture* demonSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, demonSurface);
	SDL_FreeSurface(demonSurface);

	//game title
	SDL_Surface* title = IMG_Load("assets/hell_di.png");
	SDL_SetColorKey(title, 1, SDL_MapRGB(title->format, 255, 255, 255)); 
	SDL_Texture* titleSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, title);
	SDL_FreeSurface(title);

	//Animations
	Animation anim(bloodSpriteSheetWithNoBG, renderer, 4, 64, 64, 0.5);
	Animation anim1(bloodSpriteSheetWithNoBG, renderer, 4, 64, 64, 0.5);
	Animation anim2(runSpriteSheetWithNoBG, renderer, 7, 56, 76, 0.2);
	Animation animShiny(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.1);
	Animation animShiny1(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.2);
	Animation animShiny2(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.3);
	Animation animShiny3(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.4);
	Animation animShiny4(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.5);
	Animation animShiny5(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.6);
	Animation animShiny6(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.7);
	Animation animShiny7(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.8);
	Animation animShiny8(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.1);
	Animation animShiny9(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.2);
	Animation animShiny10(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.3);
	Animation animShiny11(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.4);
	Animation animShiny12(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.5);
	Animation animShiny13(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.6);
	Animation animShiny14(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.7);
	Animation animShiny15(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.8);
	Animation animShiny16(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.1);
	Animation animShiny17(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.2);
	Animation animShiny18(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.3);
	Animation animShiny19(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.8);
	Animation animShiny20(shinySpriteSheetWithNoBG, renderer, 7, 127, 127, 0.7);
	Animation anim5(demonSpriteSheetWithNoBG, renderer, 4, 79, 71, 0.8);
	Animation animTitle(titleSpriteSheetWithNoBG, renderer, 1, 766, 99, 1);

	

	//SETUP initial game entities
	list<Entity*> entities;
	//get Entity class static pointer to list to point to the list I made in main
	Entity::entities = &entities;

	//setting up hero
	Hero* hero = new Hero();
	hero->setAnimation(&anim2);
	hero->setRenderer(renderer);
	hero->setXY(600, 350);
	hero->acceleration.x = 310; // traveling pixels
	entities.push_back(hero);

	//setting up chaser entities
	Chaser* chaser = new Chaser();
	chaser->setRenderer(renderer);
	chaser->animation = &anim5;
	chaser->position.x = 1400;
	chaser->position.y = 300;
	chaser->faceRightChaser = false;
	chaser->target = hero; 

	Chaser* chaser1 = new Chaser();
	chaser1->setRenderer(renderer);
	chaser1->animation = &anim5;
	chaser1->position.x = 500;
	chaser1->position.y = -300;
	chaser1->faceRightChaser = false;
	chaser1->target = hero;

	Chaser* chaser3 = new Chaser();
	chaser3->setRenderer(renderer);
	chaser3->animation = &anim5;
	chaser3->faceRightChaser = false;
	chaser3->position.x = 1630;
	chaser3->position.y = 300;
	chaser3->target = hero;

	Chaser* chaser4 = new Chaser();
	chaser4->setRenderer(renderer);
	chaser4->animation = &anim5;
	chaser4->faceRightChaser = false;
	chaser4->position.x = 650;
	chaser4->position.y = -490;
	chaser4->target = hero;

	Chaser* chaser5 = new Chaser();
	chaser5->setRenderer(renderer);
	chaser5->animation = &anim5;
	chaser5->faceRightChaser = false;
	chaser5->position.x = 1300;
	chaser5->position.y = 610;
	chaser5->target = hero;

	Chaser* chaser6 = new Chaser();
	chaser6->setRenderer(renderer);
	chaser6->animation = &anim5;
	chaser6->position.x = 50;
	chaser6->position.y = -400;
	chaser6->target = hero;

	Chaser* chaser7 = new Chaser();
	chaser7->setRenderer(renderer);
	chaser7->animation = &anim5;
	chaser->faceRightChaser = false;
	chaser7->position.x = 200;
	chaser7->position.y = 1350;
	chaser7->target = hero;

	Chaser* chaser8 = new Chaser();
	chaser8->setRenderer(renderer);
	chaser8->animation = &anim5;
	chaser8->faceRightChaser = false;
	chaser8->position.x = 800;
	chaser8->position.y = -350;
	chaser8->target = hero;

	Chaser* chaser9 = new Chaser();
	chaser9->setRenderer(renderer);
	chaser9->animation = &anim5;
	chaser9->faceRightChaser = false;
	chaser9->position.x = 1850;
	chaser9->position.y = 500;
	chaser9->target = hero;

	Chaser* chaser10 = new Chaser();
	chaser10->setRenderer(renderer);
	chaser10->animation = &anim5;
	chaser10->faceRightChaser = false;
	chaser10->position.x = 1900;
	chaser10->position.y = 95;
	chaser10->target = hero;


	//setting up wall
	Wall* wall1 = new Wall();
	wall1->setRenderer(renderer);
	

	Wall* wall2 = new Wall();
	wall2->setRenderer(renderer);
	

	//addding to the list
	entities.push_back(chaser);
	entities.push_back(chaser1);
	entities.push_back(chaser3);
	entities.push_back(chaser4);
	entities.push_back(chaser5);
	entities.push_back(chaser6);
	entities.push_back(chaser7);
	entities.push_back(chaser8);
	entities.push_back(chaser9);
	entities.push_back(chaser10);
	entities.push_back(wall1);
	entities.push_back(wall2);

	//input stuff
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero;

	MouseHandler mouseHandler;
	mouseHandler.hero = hero;

	GameControllerHandler controllerHandler;
	controllerHandler.hero = hero;

	//can still use abstract classses for referecing/polymorphism
	InputHandler* inputHandler = &keyboardHandler;


	// SETUP SOME TEXT
	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 30);
	SDL_Color textColor = { 255, 255, 255, 1 };
	//health text
	string healthString = "HEALTH: " + to_string(hero->health);
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, healthString.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	//text DESTINATION
	SDL_Rect textDestination;
	textDestination.x = 50;
	textDestination.y = 50;
	//query to get width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	//score text
	string scoreString = "SCORE: " + to_string(hero->score);
	SDL_Surface* textSurfaces = TTF_RenderText_Blended(font, scoreString.c_str(), textColor);
	SDL_Texture* textTextures = SDL_CreateTextureFromSurface(renderer, textSurfaces);
	SDL_FreeSurface(textSurfaces);
	//text DESTINATION
	SDL_Rect textDestinations;
	textDestinations.x = 1100;
	textDestinations.y = 50;
	//query to get width and height
	SDL_QueryTexture(textTextures, NULL, NULL, &textDestinations.w, &textDestinations.h);


	//LOAD UP SOME MUSIC
	Mix_Music* music = Mix_LoadMUS("assets/infested_city.ogg");
	if (music == NULL){
		cout << "Music failed: " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	Mix_PlayMusic(music, -1);

	//adding some sounds
	SoundManager::soundManager.loadSound("explode","assets/Laser_Shoot21.wav");
	SoundManager::soundManager.loadSound("bulletExploded", "assets/shoot_explosion.wav");
	SoundManager::soundManager.loadSound("gameOver", "assets/overr.wav");
	SoundManager::soundManager.loadSound("heroHitted", "assets/whenHit.wav");

	Uint32 lastUpdate = SDL_GetTicks();

	bool loop = true;
	while (loop){ 


		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
	
		float DT = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();
		
		SDL_Event event;

		while (SDL_PollEvent(&event)){
		
			if (event.type == SDL_QUIT){
				loop = false;
			}
		
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					loop = false;
				}
			}
			inputHandler->update(&event);

			mouseHandler.update(&event);

			controllerHandler.update(&event);

		}


		if (controllerHandler.controller == NULL)
			keyboardHandler.updateHeldKeys();//check held down keys
		else
			controllerHandler.updateSticksAndDPads();
		

		SDL_SetRenderDrawColor(renderer, 6, 16, 54,1);//background color
		SDL_RenderClear(renderer);

		//setting up animations
		anim.update(DT);
		anim.draw(2, 35, 0.7f);
		animTitle.update(DT);
		animTitle.draw(250, 200);
		anim1.update(DT);
		anim1.draw(1050, 35, 0.7f);
		//stars animation
		animShiny.update(DT);
		animShiny.draw(10, 100, 0.1f);
		animShiny1.update(DT);
		animShiny1.draw(100, 120, 0.1f);
		animShiny2.update(DT);
		animShiny2.draw(700, 140, 0.1f);
		animShiny3.update(DT);
		animShiny3.draw(300, 200, 0.1f);
		animShiny4.update(DT);
		animShiny4.draw(800, 250, 0.1f);
		animShiny5.update(DT);
		animShiny5.draw(250, 385, 0.1f);
		animShiny6.update(DT);
		animShiny6.draw(350, 400, 0.1f);
		animShiny7.update(DT);
		animShiny7.draw(180, 550, 0.1f);
		animShiny8.update(DT);
		animShiny8.draw(580, 680, 0.1f);
		animShiny9.update(DT);
		animShiny9.draw(60, 600, 0.1f);
		animShiny10.update(DT);
		animShiny10.draw(900, 450, 0.1f);
		animShiny11.update(DT);
		animShiny11.draw(750, 60, 0.1f);
		animShiny12.update(DT);
		animShiny12.draw(690, 600, 0.1f);
		animShiny13.update(DT);
		animShiny13.draw(605, 200, 0.1f);
		animShiny14.update(DT);
		animShiny14.draw(950, 100, 0.1f);
		animShiny15.update(DT);
		animShiny15.draw(990, 150, 0.1f);
		animShiny16.update(DT);
		animShiny16.draw(1000, 250, 0.1f);
		animShiny17.update(DT);
		animShiny17.draw(1015, 300, 0.1f);
		animShiny18.update(DT);
		animShiny18.draw(35, 800, 0.1f);
		animShiny19.update(DT);
		animShiny19.draw(200, 50, 0.1f);
		animShiny20.update(DT);
		animShiny20.draw(1100, 700, 0.1f);

		for each(Entity* entity in entities){
			entity->update(DT);

			if (entity->type == "chaser"){
				Chaser* chaserPtr = (Chaser*)entity;

				//if hero collides with chaser
				if (!hero->invincible && checkColision(hero->hitbox, chaserPtr->hitbox)){
					//first, needs to delete title image
					SDL_DestroyTexture(titleSpriteSheetWithNoBG);
					SoundManager::soundManager.playSound("gameOver");
					//whatever its the score minus 10
					hero->score -= 10;
					//health -100;
					hero->health -= 100;
					//turn on invinvibility timer for short time
					hero->invincible = true;
					hero->beginTimeOut();
					//hero dies
					
					hero->died();
			
				}
			}

			if (entity->type == "bullet"){
				Bullet* bulletPtr = (Bullet*)entity;

				for each(Entity* chaser in entities){

					if (chaser->type == "chaser"){

						Chaser* chaserPtr = (Chaser*)chaser;
						//if bullet collides with chaser
						if (checkColision(bulletPtr->hitbox, chaserPtr->hitbox)){
							//destroy title
							SDL_DestroyTexture(titleSpriteSheetWithNoBG);
							SoundManager::soundManager.playSound("bulletExploded");
							//+50 score
							hero->score += 50;
							//gets a next random position
							chaserPtr->setXY(randomXPosition(), randomYPosition());
							//sends the bullet far away
							bulletPtr->setXY(3000, 3000);
							//when hero gets more than 1000 score, chaser velocity increases and score is now +75
							if (hero->score >= 100){
								hero->score += 15;
								chaserPtr->velocity.x += 100;



						}

						}

					}

				}

			}

			entity->draw();
			
		}
		//rendering health points
		SDL_DestroyTexture(textTexture);
		healthString = "HEALTH: " + to_string(hero->health);
		textSurface = TTF_RenderText_Blended(font, healthString.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);

		//score points
		SDL_DestroyTexture(textTextures);
		healthString = "SCORE: " + to_string(hero->score);
		textSurfaces = TTF_RenderText_Blended(font, healthString.c_str(), textColor);
		textTextures = SDL_CreateTextureFromSurface(renderer, textSurfaces);
		SDL_FreeSurface(textSurfaces);

		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
		SDL_RenderCopy(renderer, textTextures, NULL, &textDestinations);
		SDL_RenderPresent(renderer);
		
	}
	//destroys everything
	Mix_PausedMusic();
	Mix_FreeMusic(music);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTextures);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	

	SDL_Quit();

	return 0;
}