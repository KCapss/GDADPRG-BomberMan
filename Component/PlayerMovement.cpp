#include "PlayerMovement.h"
#include "PlayerInputController.h"
#include "../AirplanePlayer.h"

#include <iostream>

PlayerMovement::PlayerMovement(string name) : AComponent(name, Script)
{

}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::perform()
{
	AirplanePlayer* airplanePlayer = (AirplanePlayer*)this->getOwner();
	PlayerInputController* inputController = (PlayerInputController*)(airplanePlayer->getComponentsofType(ComponentType::Input)[0]);

	sf::Transformable* playerTransformable = airplanePlayer->getTransformable();
	if (playerTransformable == NULL || inputController == NULL) {
		cout << "playerTransformable not found" << endl;
		return;
	}


	sf::Vector2f offset(0.0f, 0.0f);
	if (inputController->isUp()) {
		offset.y -= this->SPEED_MULLTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isDown()) {
		offset.y += this->SPEED_MULLTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isLeft()) {
		offset.x -= this->SPEED_MULLTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isRight()) {
		offset.x += this->SPEED_MULLTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	////Update its child
	//for (int i = 0; i < childList.size(); i++) {
	//	childList[i]->update(deltaTime);
	//}
}
