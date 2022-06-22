#include "PlayerMovement.h"
#include "PlayerInputController.h"


#include "../ObjectPooling/ObjectPoolHolder.h"

#include <iostream>

PlayerMovement::PlayerMovement(string name) : AComponent(name, Script)
{
	this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::perform()
{
	//AirplanePlayer* airplanePlayer = (AirplanePlayer*)this->getOwner();
	//PlayerInputController* inputController = (PlayerInputController*)(airplanePlayer->getComponentsofType(ComponentType::Input)[0]);

	//sf::Transformable* playerTransformable = airplanePlayer->getTransformable();
	//if (playerTransformable == NULL || inputController == NULL) {
	//	cout << "playerTransformable not found" << endl;
	//	return;
	//}


	//sf::Vector2f offset(0.0f, 0.0f);
	//if (inputController->isUp()) {
	//	offset.y -= this->SPEED_MULLTIPLIER;
	//	playerTransformable->move(offset * deltaTime.asSeconds());
	//}
	//else if (inputController->isDown()) {
	//	offset.y += this->SPEED_MULLTIPLIER;
	//	playerTransformable->move(offset * deltaTime.asSeconds());
	//}
	//else if (inputController->isLeft()) {
	//	offset.x -= this->SPEED_MULLTIPLIER;
	//	playerTransformable->move(offset * deltaTime.asSeconds());
	//}
	//else if (inputController->isRight()) {
	//	offset.x += this->SPEED_MULLTIPLIER;
	//	playerTransformable->move(offset * deltaTime.asSeconds());
	//}


	//this->ticks += deltaTime.asSeconds(); //preven spamming
	//if (inputController->hasFired() && this->ticks > this->BULLET_SPAWN_INTERVAL) {
	//	
	//	this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
	//	this->ticks = 0.0f;
	//	this->projectilePool->requestPoolable();
	//}
	
}
