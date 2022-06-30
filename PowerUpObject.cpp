#include "PowerUpObject.h"

//Manager
#include "TextureManager.h"
#include "Game.h"

#include "TileMapState.h"

//Pooling
#include "ObjectPooling/GameObjectPool.h"
#include "ObjectPooling/ObjectPoolHolder.h"



#include "Component/Renderer.h"
//#include "Component/EnemyBehavior.h"

PowerUpObject::PowerUpObject(string name): APoolable(name), CollisionListener()
{
}

PowerUpObject::~PowerUpObject()
{
	AGameObject::~AGameObject();
}

void PowerUpObject::initialize()
{
}

void PowerUpObject::onRelease()
{

}

void PowerUpObject::onActivate()
{
}

APoolable* PowerUpObject::clone()
{
	return nullptr;
}

void PowerUpObject::onCollisionEnter(AGameObject* contact)
{
}

void PowerUpObject::onCollisionExit(AGameObject* contact)
{
}

bool PowerUpObject::hitConfirmed()
{
	return false;
}

void PowerUpObject::resetHit()
{
}
