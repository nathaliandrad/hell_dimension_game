#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	//release memory of loaded up sounds
	for each(SoundListing listing in sounds){
		Mix_FreeChunk(listing.sound);
	}
}


void SoundManager::loadSound(string name, string file){
	SoundListing listing;
	listing.name = name;
	listing.sound = Mix_LoadWAV(file.c_str());

	//add to list
	sounds.push_back(listing);
}
void SoundManager::playSound(string name){
	for (SoundListing listing : sounds){
		//if find match by name
		if (listing.name == name){
			//play sound
			//params: channel to play on(-1 means find free channel)
			//	sound to play
			//	how many loops(0 means play one, -1 infinetely)
			Mix_PlayChannel(-1, listing.sound, 0);
			break; //exiting loop
		}
	
	}
}

//type			class::static variable
SoundManager SoundManager:: soundManager;


