#pragma once
#include <SDL_mixer.h>
#include <string>
#include <list>

using namespace std;

struct SoundListing{
	Mix_Chunk* sound;
	string name;
	
};

class SoundManager
{
public:
	list<SoundListing> sounds;
	
	SoundManager();
	~SoundManager();
	void loadSound(string name, string file);
	void playSound(string name);

	static SoundManager soundManager;
};

