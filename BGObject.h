#pragma once
#include "TextureManager.h"
#include "AGameObject.h"
#include "Game.h"

class BGObject: public AGameObject
{
public:
	BGObject(std::string name);
	void initialize();
	/*void processInput(sf::Event event); */
	/*void update(sf::Time deltaTime);*/

private:
	const float SPEED_MULTIPLIER = 100.0f;

};

