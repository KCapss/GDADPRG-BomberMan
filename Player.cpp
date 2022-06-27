#include "Player.h"
#include "TextureManager.h"
#include "Game.h"

#include"Component/PlayerInputController.h"
#include"Component/PlayerMovement.h"
#include"Component/Renderer.h"

#include <iostream>

Player::Player(std::string name): AGameObject(name)
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

	//Declared
	Renderer* renderer = new Renderer("Player Sprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

}
