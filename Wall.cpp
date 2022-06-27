#include "Wall.h"
#include "TextureManager.h"
#include "Game.h"

#include"Component/PlayerInputController.h"
#include"Component/PlayerMovement.h"
#include"Component/Renderer.h"
#include <iostream>

Wall::Wall(std::string name, WallTypes wallType) : AGameObject(name), CollisionListener()
{
	this->wallType = wallType;
}

void Wall::initialize()
{
	//std::cout << " Declared as " << this->getName() << std::endl;


//Render Object Sprite
	this->sprite = new sf::Sprite();

	if (wallType != WallTypes::Ground) {
		sprite->setTexture(*TextureManager::getInstance()->getTexture("wall"));
	}

	else if (wallType == WallTypes::Ground) {
		sprite->setTexture(*TextureManager::getInstance()->getTexture("ground"));
	}


	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x/2 , textureSize.y / 2);
	//this->transformable.setScale(sf::sc)
	

	//Wall Covering
	if (wallType == WallTypes::Top) {
		this->transformable.setPosition(textureSize.x/2, (textureSize.y / 2) + 64.0f);
		sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x * 17, textureSize.y));
	}

	else if (wallType == WallTypes::Left) {
		this->transformable.setPosition(textureSize.x / 2, (textureSize.y / 2) + (textureSize.y * 2));
		sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y * 11));
	}

	else if (wallType == WallTypes::Right) {
		this->transformable.setPosition(textureSize.x / 2 + (textureSize.x * 16), (textureSize.y / 2) + (textureSize.y * 2));
		sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y * 11));
	}
	else if (wallType == WallTypes::Bottom) {
		this->transformable.setPosition(textureSize.x / 2, (textureSize.y / 2) + (textureSize.y * 13));
		sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x * 17, textureSize.y));
	}
	else if (wallType == WallTypes::Ground) {
		this->transformable.setPosition(textureSize.x / 2, (textureSize.y / 2) + 64.0f);
		sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x * 17, textureSize.y * 13));
	}


	else if (wallType == WallTypes::Center) {
		/*sf::FloatRect main;
		sf::FloatRect bounds = this->sprite->getGlobalBounds();
		bounds = sf::FloatRect(bounds.left, bounds.top, textureSize.x, textureSize.y);*/
	}

//Declared Renderer
	Renderer* renderer = new Renderer("Wall Sprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);


// Attach Component
	if (wallType != WallTypes::Ground && wallType == WallTypes::Center) {

		this->collider = new Collider("Wall");
		collider->setLocalBounds(sprite->getGlobalBounds());
		collider->setCollisionListener(this);
		this->attachComponent(collider);

		PathManager::getInstance()->trackWallObject(this->collider);
	}
		

	else if (wallType == WallTypes::Ground)
		this->collider = new Collider("Ground");


}

void Wall::initialPos(sf::Vector2f pos)
{
	this->setPosition(pos.x, pos.y);
	/*cout << "Wall Position  X: " << pos.x
		<< "  Y: " << pos.y << endl;*/
}

void Wall::onCollisionEnter(AGameObject* contact)
{
}

void Wall::onCollisionExit(AGameObject* gameObject)
{
}
