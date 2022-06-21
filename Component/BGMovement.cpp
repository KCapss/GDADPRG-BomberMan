#include "BGMovement.h"
#include "../Game.h"
#include "../BGObject.h"
#include <iostream>

BGMovement::BGMovement(string name): AComponent(name, Script)
{

}

BGMovement::~BGMovement()
{
}

void BGMovement::perform()
{
	BGObject* bgObject = (BGObject*)this->getOwner();
	sf::Transformable* BGTransformable = bgObject->getTransformable();

	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;
	BGTransformable->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = BGTransformable->getPosition();
	/*std::cout << "X: " << localPos.x << "Y: " << localPos.y << std::endl;
	std::cout << "X: " << localPos.x << "Y: "  << localPos.y << std::endl;*/
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//Reset Position
		BGTransformable->setPosition(0, -Game::GAME_WINDOW_HEIGHT * 7);
	}

}


