#include "Player.h"
#include "TextureManager.h"
#include "Game.h"

#include "PlayerState.h"

#include"Component/PlayerInputController.h"
#include"Component/PlayerMovement.h"
#include"Component/Renderer.h"

#include <iostream>




Player::Player(std::string name): AGameObject(name), CollisionListener()
{
	
}

void Player::initialize()
{
	std::cout << " Declared as " << this->getName() << std::endl;
	
	//initialize Sprite
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bomberMan"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(Game::GAME_WINDOW_WIDTH / 2, Game::GAME_WINDOW_HEIGHT / 2);
	this->transformable.setScale(sf::Vector2f(0.9f, 0.83f));

	//Declared
	Renderer* renderer = new Renderer("Player Sprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	this->collider = new Collider("Player");
	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	PhysicsManager::getInstance()->trackObject(this->collider);
	PathManager::getInstance()->trackObject(this->collider);

}

void Player::changeOrientation(ObjectFacing playerOrientation)
{
	this->playerOrientation = playerOrientation;
}

void Player::changeBlockStatus(bool flag)
{
	this->isBlocked = flag;
	
}

void Player::incrementSpeed(float speed)
{
	this->SPEED_MULLTIPLIER += speed;
}

ObjectFacing Player::retrieveOrientation()
{
	return this->playerOrientation;
}

bool Player::getBlockedStatus()
{
	return this->isBlocked;
}

float Player::retrieveSpeed()
{
	return SPEED_MULLTIPLIER;
}

void Player::onCollisionEnter(AGameObject* contact)
{
	//if (contact->getName().find("Wall") != std::string::npos) {
	//	this->isBlocked = true;
	//	//cout << "Collision Detected" << endl;
	//}

	//cout << " you died" << endl;
	//cout << "Collision Monster with " << contact->getName() << endl;

	if (contact->getName().find("enemy") != std::string::npos) {
		cout << " you died" << endl;
	}

	if (contact->getName().find("VFX") != std::string::npos) {
		cout << " you died" << endl;
	}


	//For PowerUP
	if (contact->getName().find("IncreaseBombCount") != std::string::npos) {
		PlayerState::getInstance()->incrementBombCount();
		cout << " you hit PowerUPBomb" << endl;
	}

	if (contact->getName().find("PowerIncrease") != std::string::npos) {
		PlayerState::getInstance()->incrementMaxRange();
		cout << " you hit PowerUPPower" << endl;
	}

	if (contact->getName().find("IncreasSpeed") != std::string::npos) {
		
		this->incrementSpeed(100.0f);
		cout << " you hit PowerUPSpeed" << endl;
	}

	if (contact->getName().find("Detonator") != std::string::npos) {
		cout << " you hit PowerUPDetonate" << endl;
	}
	
}

void Player::onCollisionExit(AGameObject* gameObject)
{
}

void Player::incrementBombUsedCount(int count)
{
	this->usedBombCount += count;
}

int Player::getUsedBombCount()
{
	return this->usedBombCount;
}
