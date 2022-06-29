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

void PlayerState::incrementBombCount()
{
	this->maxBombCount++;
}

void PlayerState::incrementMaxRange()
{
	this->maxRange++;
}

void PlayerState::incrementEnemCount(int count)
{
	this->enemRemains += count;
}

void PlayerState::incrementScore(int score)
{
	this->score += score;
}

void PlayerState::resetLevel()
{
	this->maxBombCount = 1;
	this->maxRange = 1;
}


