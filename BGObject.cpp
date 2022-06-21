#include "BGObject.h"
#include <iostream>
#include "Component/Renderer.h"
#include "Component/BGMovement.h"

BGObject::BGObject(std::string name): AGameObject(name)
{

}

void BGObject::initialize()
{
	//std::cout << "Declared as " << this->getName() << std::endl;

	////assignTexture
	//sprite = new sf::Sprite();
	//sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
	//sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	////make BG height x k to emulate repeating BG;
	//sprite->setTextureRect(sf::IntRect(0, 0, Game::GAME_WINDOW_WIDTH, Game::GAME_WINDOW_HEIGHT * 8));
	//sprite->setPosition(0, -Game::GAME_WINDOW_HEIGHT * 7);

	
	//assignTexture
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	//make BG height x k to emulate repeating BG;
	sprite->setTextureRect(sf::IntRect(0, 0, Game::GAME_WINDOW_WIDTH, Game::GAME_WINDOW_HEIGHT * 8));
	/*sprite->setPosition(0, -Game::GAME_WINDOW_HEIGHT * 7);*/
	sprite->setPosition(0, 0);

	Renderer* renderer = new Renderer("BGRenderer");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	BGMovement* logicComponent = new BGMovement ("BGMovement");
	this->attachComponent(logicComponent);



}

//void BGObject::processInput(sf::Event event)
//{
//
//
//
//}

//void BGObject::update(sf::Time deltaTime)
//{
//	//make BG roll Slowly
//	//sf::Vector2f offset(0.0f, 0.0f);
//	sf::Vector2f offset(0.0f, 0.0f);
//	offset.y += SPEED_MULTIPLIER;
//	//sprite->move(offset * deltaTime.asSeconds());
//	sprite->move(offset * deltaTime.asSeconds());
//
//	sf::Vector2f localPos = sprite->getPosition();
//	/*std::cout << "X: " << localPos.x << "Y: " << localPos.y << std::endl;
//	std::cout << "X: " << localPos.x << "Y: "  << localPos.y << std::endl;*/
//	if (localPos.y * deltaTime.asSeconds() > 0) {
//		//Reset Position
//		sprite->setPosition(0, -Game::GAME_WINDOW_HEIGHT * 7);
//	}
//
//
//}
