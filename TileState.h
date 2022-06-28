#pragma once
#include "AGameObject.h"
#include "Player.h"
class TileState
{
public:
	//Constructor
	TileState();
	void initialize(sf::Vector2f Position, std::string name);

	//Getter
	sf::Vector2f getPosition();
	bool isOccupied();



private:
	string name;
	bool haveAccess = true;
	sf::Vector2f position = sf::Vector2f(0, 0);

};

