#include "TileState.h"


TileState::TileState()
{
}

void TileState::initialize(sf::Vector2f Position, std::string name)
{
    this->position = Position;
    this->name = name;

    this->haveAccess = false;
}

void TileState::reset()
{
    this->position = sf::Vector2f(0, 0);
    this->name = "";

    this->haveAccess = true;
}

void TileState::resetExplosion()
{
    this->explosionStart = false;
    this->explosionActive = false;
}


sf::Vector2f TileState::getPosition()
{
    return this->position;
}

std::string TileState::getName()
{
    return this->name;
}

bool TileState::hasExploded()
{
    return this->explosionActive;
}

bool TileState::hasinitiateExplosion()
{
    return this->explosionStart;
}

bool TileState::isOccupied()
{
    return this->haveAccess;
}

void TileState::activateExplosion()
{
    this->explosionStart = true;
}

void TileState::explosionSetActive()
{
    this->explosionActive = true;
}
