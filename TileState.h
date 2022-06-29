#pragma once
#include "AGameObject.h"
#include "Player.h"
class TileState
{
public:
	//Constructor
	TileState();
	void initialize(sf::Vector2f Position, std::string name);

	void reset();
	void resetExplosion();

	//Getter
	sf::Vector2f getPosition();
	std::string getName();
	bool hasExploded();
	bool hasinitiateExplosion();
	bool isOccupied();

	//Setter
	void activateExplosion();
	void explosionSetActive();

private:
	string name;
	bool haveAccess = true;
	bool explosionActive = false;
	bool explosionStart = false;
	sf::Vector2f position = sf::Vector2f(0, 0);

};

