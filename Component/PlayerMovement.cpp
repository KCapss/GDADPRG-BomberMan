#include "PlayerMovement.h"



#include "../ObjectPooling/ObjectPoolHolder.h"


#include <iostream>

PlayerMovement::PlayerMovement(string name) : AComponent(name, Script)
{
	//this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
}

PlayerMovement::~PlayerMovement()
{
}

void PlayerMovement::perform()
{
	Player* player = (Player*)this->getOwner();
	PlayerInputController* inputController = (PlayerInputController*)(player->getComponentsofType(ComponentType::Input)[0]);

	sf::Transformable* playerTransformable = player->getTransformable();
	if (playerTransformable == NULL || inputController == NULL) {
		cout << "playerTransformable not found" << endl;
		return;
	}

	sf::Vector2f offset(0.0f, 0.0f);

	//PathManager::getInstance()->operate();

	if (this->checkOutofBounds(player, inputController) && 
		!player->getBlockedStatus() &&
		this->checkWalls(player, inputController)) 
	{


		if (inputController->isUp()) {
			offset.y -= this->SPEED_MULLTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
			player->changeOrientation(PlayerFacing::playerUp);
		}
		if (inputController->isDown()) {
			offset.y += this->SPEED_MULLTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
			player->changeOrientation(PlayerFacing::playerDown);
		}
		if (inputController->isLeft()) {
			offset.x -= this->SPEED_MULLTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
			player->changeOrientation(PlayerFacing::playerLeft);
		}
		if (inputController->isRight()) {
			offset.x += this->SPEED_MULLTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
			player->changeOrientation(PlayerFacing::playerRight);
		}
	}

	else if (this->checkOutofBounds(player, inputController) && player->getBlockedStatus()) {
		adjustPos(player);
	}


	//this->ticks += deltaTime.asSeconds(); //preven spamming
	//if (inputController->hasFired() && this->ticks > this->BULLET_SPAWN_INTERVAL) {
	//	
	//	this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
	//	this->ticks = 0.0f;
	//	this->projectilePool->requestPoolable();
	//}
	
}

void PlayerMovement::adjustPos(Player* player)
{
	float xPos = player->getTransformable()->getPosition().x;
	float yPos = player->getTransformable()->getPosition().y;
	sf::Transformable* playerTransformable = player->getTransformable();
	sf::Vector2f offset(0.0f, 0.0f);


	if (player->retrieveOrientation() == PlayerFacing::playerUp) {
		offset.y += this->SPEED_MULLTIPLIER;
		playerTransformable->setPosition(sf::Vector2f(xPos, yPos + (offset.y * deltaTime.asSeconds())));
	}

	if (player->retrieveOrientation() == PlayerFacing::playerDown) {
		offset.y -= this->SPEED_MULLTIPLIER;
		playerTransformable->setPosition(sf::Vector2f(xPos, yPos + (offset.y * deltaTime.asSeconds())));
	}

	if (player->retrieveOrientation() == PlayerFacing::playerLeft) {
		offset.x += this->SPEED_MULLTIPLIER;
		playerTransformable->setPosition(sf::Vector2f(xPos + (offset.x * deltaTime.asSeconds()), yPos ));
	}

	if (player->retrieveOrientation() == PlayerFacing::playerRight) {
		offset.x -= this->SPEED_MULLTIPLIER;
		playerTransformable->setPosition(sf::Vector2f(xPos + (offset.x * deltaTime.asSeconds()), yPos));
	}

	player->changeBlockStatus(false);
}

bool PlayerMovement::checkOutofBounds(Player* player, PlayerInputController *inputController)
{
	float xPos = player->getTransformable()->getPosition().x;
	float yPos = player->getTransformable()->getPosition().y;

	//Self-Defined Boundaries
	float LBound = 64.0f + 32.0f;
	float RBound = (64.0f * 15) + 32.0f;
	float TBound = (64.0f * 2) + 32.0f;
	float BBound = (64.0f * (2 + 10)) + 32.0f;
	sf::Vector2f offset(0.0f, 0.0f);

	if (inputController->isUp()) {
		offset.y -= this->SPEED_MULLTIPLIER * deltaTime.asSeconds();
		if (yPos + offset.y < TBound) {
			return false;
		}
		

	}
	if (inputController->isDown()) {
		offset.y += this->SPEED_MULLTIPLIER * deltaTime.asSeconds();
		if (yPos + offset.y > BBound) {
			return false;
		}
		
		
	}
	if (inputController->isLeft()) {
		offset.x -= this->SPEED_MULLTIPLIER * deltaTime.asSeconds();
		if (xPos + offset.x < LBound) {
			return false;
		}
		
		
	}
	if (inputController->isRight()) {
		offset.x += this->SPEED_MULLTIPLIER * deltaTime.asSeconds();
		if (xPos + offset.x > RBound) {
			return false;
		}
		
	}

	else
		return true;
}

bool PlayerMovement::checkWalls(Player* player, PlayerInputController* inputController)
{

	PlayerFacing orientation;

	if (inputController->isUp()) {
		orientation = PlayerFacing::playerUp;
		//cout << "Up" << endl;
		if (PathManager::getInstance()->predictMovement((Collider*)player->getComponentsofType(Physics)[0],
			orientation)) {
			return true;
		}

		else return false;
	}
	if (inputController->isDown()) {
		orientation = PlayerFacing::playerDown;
		//cout << "Down" << endl;
		if (PathManager::getInstance()->predictMovement((Collider*)player->getComponentsofType(Physics)[0],
			orientation)) {
			return true;
		}

		else return false;

	}
	if (inputController->isLeft()) {
		orientation = PlayerFacing::playerLeft;
		//cout << "Left" << endl;
		if (PathManager::getInstance()->predictMovement((Collider*)player->getComponentsofType(Physics)[0],
			orientation)) {
			return true;
		}

		else return false;

	}
	if (inputController->isRight()) {
		orientation = PlayerFacing::playerRight;
		//cout << "Right" << endl;
		if (PathManager::getInstance()->predictMovement((Collider*)player->getComponentsofType(Physics)[0],
			orientation)) {
			return true;
		}

		else return false;
	}
	return false;
}
