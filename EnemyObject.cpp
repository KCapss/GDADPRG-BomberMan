#include "EnemyObject.h"


//Manager
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "TileMapState.h"
#include "Physics/PathManager.h"


//Component
#include "Component/EnemyBehaviour.h"

//Others

#include "ObjectPooling/ObjectPoolHolder.h"
#include "Screen/HUD.h"
#include "Component/Renderer.h"
#include <iostream>


EnemyObject::EnemyObject(std::string name) : APoolable(name), CollisionListener()
{
}

void EnemyObject::initialize()
{
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("enem_1"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    //sprite->setScale(0.9f, 0.9f);

    Renderer* renderer = new Renderer("Enemy");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    this->collider = new Collider("EnemyCollider");
    collider->setLocalBounds(sprite->getGlobalBounds());
    collider->setCollisionListener(this);
    this->attachComponent(collider);

    EnemyBehaviour* enemyBehaviour = new EnemyBehaviour("EnemyBehaviour");
    this->attachComponent(enemyBehaviour);

}

void EnemyObject::onRelease()
{

    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void EnemyObject::onActivate()
{
    //Randomize Spawning
    tempPos = TileMapState::getInstance()->randomizeSpawn("Enemy");
    this->setPosition(tempPos.x, tempPos.y);
    collider->setLocalBounds(sprite->getGlobalBounds());

    //Initialize Component
    PhysicsManager::getInstance()->trackObject(this->collider);

}

APoolable* EnemyObject::clone()
{
    APoolable* copyObj = new EnemyObject(this->name);
    return copyObj;
}

void EnemyObject::onCollisionEnter(AGameObject* contact)
{
    
    if (contact->getName().find("VFX") != std::string::npos) {
        GameObjectPool* enemPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
        enemPool->releasePoolable((APoolable*)this);
    }
}

void EnemyObject::onCollisionExit(AGameObject* gameObject)
{
}

float EnemyObject::retrieveSpeed()
{
    return this->ENEM_SPEED_MULLTIPLIER;
}

ObjectFacing EnemyObject::retrieveEnemOrientation()
{
    return this->enemFacing;
}

int EnemyObject::getIQ()
{
    return this->IQ;
}

void EnemyObject::changeOrientation(ObjectFacing enemOrientation)
{
    this->enemFacing = enemOrientation;
}
