
#include "DoorObject.h"

#include "PlayerState.h"
#include "TileMapState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Scene/SceneManager.h"


#include"Component/Renderer.h"
#include <iostream>

DoorObject::DoorObject(std::string name) : AGameObject(name), CollisionListener()
{
}

DoorObject::~DoorObject()
{

	TileMapState::getInstance()->unRegisterPosition(tempPos);
	//PhysicsManager::getInstance()->untrackObject(this->collider);

	//AGameObject::~AGameObject();
}

void DoorObject::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("Door"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->sprite->setScale(0.8f, 0.8f);

	tempPos = TileMapState::getInstance()->randomizeSpawn("EndLevel");
	this->sprite->setPosition(tempPos);
	

	// Declared Renderer
	Renderer * renderer = new Renderer("Wall Sprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->collider = new Collider("Door");
	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	

	TileMapState::getInstance()->registerPosition(tempPos, "EndLevel");
	PhysicsManager::getInstance()->trackObject(this->collider);
}

void DoorObject::onCollisionEnter(AGameObject* contact)
{
	if (contact->getName().find("Player") != std::string::npos
		&& PlayerState::getInstance()->retrieveEnemCount() == 0) {


		//Create A SFX
		
		
		//Generate Different Level
		int levelNum = TileMapState::getInstance()->getLevelSceneNum();

		if (levelNum >= 3) {
			SceneManager::getInstance()->loadScene( "TitleScene");
		}
		else {
			SceneManager::getInstance()->loadScene( "Level_" + to_string(levelNum + 1));
		}
		

		
	//
	}
}

void DoorObject::onCollisionExit(AGameObject* gameObject)
{
}
