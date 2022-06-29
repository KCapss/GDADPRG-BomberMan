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
}

void BombVFX::onActivate()
{
	this->tempPos = TileMapState::getInstance()->onInitiateExplotion();
	this->setPosition(tempPos.x, tempPos.y);
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
			GameObjectPool* VFXBombPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::VFX_POOL_TAG);
			VFXBombPool->releasePoolable((APoolable*)this);
		}
		
	}
}

void BombVFX::onCollisionEnter(AGameObject* contatct)
{
}

void BombVFX::onCollisionExit(AGameObject* contact)
{
}