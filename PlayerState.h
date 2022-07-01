#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum PowerUPType {
	PowerIncrease = 0,
	IncreaseBombCount = 1,
	IncreasSpeed = 2,
	Detonator = 3,
};

class PlayerState: sf::NonCopyable
{

public:
	static PlayerState* getInstance();
	void initialize();

	//Getter for Player
	void updatePos(sf::Vector2f pos);
	sf::Vector2f retrievePlayerPos();

	//Getter Function
	int retrieveMaxRange();
	int retrieveMaxBombCount();

	int retrieveEnemCount();
	int retrieveScore();

	//Setter
	void incrementBombCount();
	void incrementMaxRange();

	void setEnemCount(int count);
	void incrementEnemCount(int count);
	void incrementScore(int score);

	//Power Up
	void setActivePowerUp(PowerUPType type);
	PowerUPType retrieveActivePowerUPType();
	


	//Reset Level
	void resetLevel();

private:
	//set constructor to private
	PlayerState() {};

	static PlayerState* sharedInstance;

	sf::Vector2f playerPos = sf::Vector2f(0, 0);

	//Player Properties
	int maxBombCount = 1;
	int maxRange = 1;

	//int tempIncreaseBombCount = 0;
	//int tempIncrease

	//UI or Game Properties
	int enemRemains = 0;
	int score = 0;

	PowerUPType levelPowerUP = Detonator;

};

