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


sf::Vector2f TileState::getPosition()
{
    return sf::Vector2f();
}

bool TileState::isOccupied()
{
    return this->haveAccess;
}
