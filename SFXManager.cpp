#include <stddef.h>
#include <iostream>
#include "SFXManager.h"


SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance()
{
	//initial only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}

	return sharedInstance;
}

void SFXManager::loadAll()
{
//Load All Music


//Load All SFX
	//Object Spawning
	loadSoundBuffer("explode", "Media/Assets/SFX/BombExplosion.ogg");
	loadSoundBuffer("placeBombs", "Media/Assets/SFX/BombPlacement.ogg");
	

	//VFX or UI
	loadSoundBuffer("click", "Media/Assets/SFX/mouseClick.ogg");


}

sf::SoundBuffer* SFXManager::getSoundBuffer(std::string key)
{
	if (soundBufferMap[key] != NULL) {
		return soundBufferMap[key];
	}

	else {
		std::cout << "No SoundBuffer found for " << key << std::endl;
		return NULL;
	}
}

sf::Music* SFXManager::getMusicFile(std::string key)
{
	if (musicMap[key] != NULL) {
		return musicMap[key];
	}

	else {
		std::cout << "No MusicMap found for " << key << std::endl;
		return NULL;
	}
}

void SFXManager::loadSoundBuffer(std::string key, std::string path)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
	soundBuffer->loadFromFile(path);
	soundBufferMap[key] = soundBuffer;
}

void SFXManager::loadMusic(std::string key, std::string path)
{
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(path)) {
		std::cout << "error loading music for " << path << std::endl;
	}
	
	else {
		musicMap[key] = music;
	}
	
}
