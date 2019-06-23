#include "Hero.h"
#include <fstream>
#include <iostream>


Hero::Hero()
{
	type = "hero";
	animation = NULL;
	faceRight = true;
	health = 1000;
	hitbox.w = 20;
	hitbox.h = 50;
	score = 0;
}


Hero::~Hero()
{
}


void Hero::setAnimation(Animation* animation){
	this->animation = animation;
}


void Hero::shoot(){


	Bullet* bullet = new Bullet();
	bullet->setRenderer(renderer);
	bullet->setXY(position.x + 50, position.y + 20);
	
	bullet->movementSpeed = 420; //200px per second

	if (animation != NULL){

		if (faceRight){
			animation->draw(position.x , position.y );
			//straight bullet to the right
			bullet->angle = 6.3;

		}
		else{
			animation->draw(position.x , position.y, true);
			bullet->setXY(position.x, position.y + 20);
			//straight bullet to the left
			bullet->angle = 3.1;
		}
	}

	//add to list of entities
	Entity::entities->push_back(bullet);

	SoundManager::soundManager.playSound("explode");
}



void Hero::update(float dt){

	if (timeoutActive){
		invincibleTimer -= dt;
		if (invincibleTimer <= 0){
			timeoutActive = false;
			invincible = false;
		}
	}

	

	if (velocity.x > 0){
		faceRight = true;

	}
	if (velocity.x < 0){
		faceRight = false;

	}

	//lazy friction force to apply to acceleration
	Vector friction(-0.4* (velocity.x), -0.4 * (velocity.y));

	acceleration.x += friction.x;
	acceleration.y += friction.y;

	//update movement based on velocity
	updateMovement(dt);
	
	//updating hero hitbox correctly
	hitbox.x = position.x + 15;
	hitbox.y = position.y + 15;


	if (animation != NULL)
		animation->update(dt);

}


void Hero::draw(){


	SDL_SetRenderDrawColor(renderer, 6, 16, 54, 1);
	SDL_Rect hitboxCam = { hitbox.x, hitbox.y, hitbox.w, hitbox.h };
	SDL_RenderFillRect(renderer, &hitboxCam);

	if (animation != NULL){

		if (faceRight){
			animation->draw(position.x , position.y );

		}
		else{
			animation->draw(position.x , position.y , true);

		}
	}


}

void Hero::beginTimeOut(){
	
	//so hero can be invincible for a short time
		timeoutActive = true;
		invincibleTimer = 1.3;

}

void Hero::died(){

	//getting highest score
	float highScore = 0;
	float currentScore = 0;
	

	if (health <= 0){
		currentScore = score;
		ifstream fin;
		fin.open("hell_highScore.txt");
		if (fin.is_open()){
			fin >> highScore;
			cout << "\n\n\tGAME OVER!";
			cout << "\n\n\t Current score: " << currentScore;
			cout << "\n\n\t Latest Highest score: " << highScore;

		}
		else{
			cout << "Error opening file";
		}

		fin.close();

		if (currentScore >= highScore){
			highScore = currentScore;
			string name;
			cout << "\n\n\tCONGRATULATIONS!";
			cout << "\n\n\t\tNew HighScore!!!\n\n";
			cout << "\n\n\t Latest HighScore: " << highScore << endl << endl;
			//	cout << "Please enter your Name: ";
			//	cin.ignore(1000, '\n');
			//	getline(cin, name);

			ofstream fout;
			fout.open("hell_highScore.txt", ios::trunc);
			if (fout.good())
				fout << highScore; //writes on the file, name and score

			fout.close();


		}


		SDL_DestroyRenderer(renderer);
		SDL_Quit();

		
	}

}




