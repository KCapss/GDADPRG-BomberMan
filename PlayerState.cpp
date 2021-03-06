#include "PlayerState.h"

PlayerState* PlayerState::sharedInstance = NULL;

PlayerState* PlayerState::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new PlayerState();
	}

	return sharedInstance;
}

void PlayerState::initialize()
{
	this->maxRange = 1;
	this->maxBombCount = 2;
}

void PlayerState::updatePos(sf::Vector2f pos)
{
	this->playerPos = pos;
}

sf::Vector2f PlayerState::retrievePlayerPos()
{
	return this->playerPos;
}

int PlayerState::retrieveMaxRange()
{
	return this->maxRange;
}

int PlayerState::retrieveMaxBombCount()
{
	return this->maxBombCount;
}

int PlayerState::retrieveEnemCount()
{
	return this->enemRemains;
}

int PlayerState::retrieveScore()
{
	return this->score;
}

bool PlayerState::isPlayerAlive()
{
	return this->isAlive;
}

void PlayerState::incrementBombCount()
{
	this->maxBombCount++;
}

void PlayerState::incrementMaxRange()
{
	this->maxRange++;
}

void PlayerState::setEnemCount(int count)
{
	this->enemRemains = count;
}

void PlayerState::incrementEnemCount(int count)
{
	this->enemRemains += count;
}

void PlayerState::incrementScore(int score)
{
	this->score += score;
}

void PlayerState::setAliveState(bool flag)
{
	this->isAlive = flag;
}

void PlayerState::setActivePowerUp(PowerUPType type)
{
	this->levelPowerUP = type;
}

PowerUPType PlayerState::retrieveActivePowerUPType()
{
	return this->levelPowerUP;
}

void PlayerState::resetLevel()
{
	this->maxBombCount = 2;
	this->maxRange = 1;

	this->isAlive = true;
}


