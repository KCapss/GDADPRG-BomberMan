#include "BoxObject.h"

//Manager
#include "TextureManager.h"
#include "Game.h"

#include "TileMapState.h"

//Pooling
#include "ObjectPooling/GameObjectPool.h"
#include "ObjectPooling/ObjectPoolHolder.h"



#include "Component/Renderer.h"
//#include "Component/EnemyBehavior.h"
BoxObject::BoxObject(std::string name): APoolable(name), CollisionListener()
{
}

void BoxObject::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("defaultCrate"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x/2, textureSize.y/2);
	this->setPosition(96.0f, 170.0f);

	

	Renderer* renderer = new Renderer("BoxSprite");
	renderer->assignDrawable(sprite);
	//renderer->assignDrawable(sprite);

	this->attachComponent(renderer);


	this->collider = new Collider("Box");

	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);
}

void BoxObject::onRelease()
{
	//PhysicsManager::getInstance()->untrackObject(this->collider);
}

void BoxObject::onActivate()
{
	//this->setPosition(192.0f, 192.0f);
	sf::Vector2f position(0, 0);
	
	position = TileMapState::getInstance()->randomizeSpawn(this->name);
	TileMapState::getInstance()->registerPosition(position, this->name);

	this->getTransformable()->setPosition(position);
	/*cout << "X: " << position.x <<
		" Y: " << position.y << endl;*/
	//Debugger


	//Collider
	PathManager::getInstance()->trackWallObject(this->collider);
	
}

APoolable* BoxObject::clone()
{
	APoolable* copyObj = new BoxObject(this->name);
	return copyObj;
}

void BoxObject::onCollisionEnter(AGameObject* contact)
{
	//Whenever the bomb collided with other objects
	
}

void BoxObject::onCollisionExit(AGameObject* gameObject)
{
	//Activate the collider for the physics
	PathManager::getInstance()->untrackWallObject(this->collider);
	TileMapState::getInstance()->unRegisterPosition(this->getTransformable()->getPosition());


	GameObjectPool* boxPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BOX_POOL_TAG);
	boxPool->releasePoolable((APoolable*)this);
	//PhysicsManager::getInstance()->trackObject(this->collider);

}
