#include "BombVFX.h"

#include "TextureManager.h"
#include "GameObjectManager.h"
#include "TileMapState.h"


#include "ObjectPooling/ObjectPoolHolder.h"
//#include "Screen/HUD.h"
#include "Component/Renderer.h"
#include <iostream>

BombVFX::BombVFX(string name) : APoolable(name), CollisionListener()
{
}

BombVFX::~BombVFX()
{
	AGameObject::~AGameObject();
}

void BombVFX::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bombVFX"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x/2, textureSize.y/2);
	sprite->setScale(0.6f, 0.6f);


	Renderer* renderer = new Renderer("BombVFX");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->collider = new Collider("BOMB VFX");

	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);
}

void BombVFX::onRelease()
{
	TileMapState::getInstance()->unregisterExplosion(tempPos);
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void BombVFX::onActivate()
{
	this->tempPos = TileMapState::getInstance()->onInitiateExplotion();
	this->setPosition(tempPos.x, tempPos.y);

	PhysicsManager::getInstance()->trackObject(this->collider);
	//collider->setLocalBounds(sprite->getGlobalBounds());
}

APoolable* BombVFX::clone()
{
	APoolable* copyObj = new BombVFX(this->name);
	return copyObj;
}

void BombVFX::update(sf::Time deltaTime)
{
	if (isEnabled()) {

		ticks += deltaTime.asSeconds();
		
		if (ticks > BOMB_DURATION) {
			ticks = 0;

			
			sf::FloatRect bounds = sf::FloatRect(tempPos.x - 32, tempPos.y, 64.0f, 64.0f);


			PathManager::getInstance()->checkIntersection(this->collider, bounds);
			GameObjectPool* VFXBombPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::VFX_POOL_TAG);
			VFXBombPool->releasePoolable((APoolable*)this);
		}
		
	}
}

void BombVFX::onCollisionEnter(AGameObject* contact)
{
	//cout << "Collided with: " << contact->getName() << endl;



}

void BombVFX::onCollisionExit(AGameObject* contact)
{
}
