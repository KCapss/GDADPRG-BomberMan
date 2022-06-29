#include "BombObject.h"

//Parent
#include "Player.h"

//Manager
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "TileMapState.h"
#include "Physics/PathManager.h"


//Component


//Others

#include "ObjectPooling/ObjectPoolHolder.h"
#include "Screen/HUD.h"
#include "Component/Renderer.h"
#include <iostream>

BombObject::BombObject(string name): APoolable(name), CollisionListener()
{

}

BombObject::~BombObject()
{
    AGameObject::~AGameObject();
}

void BombObject::initialize()
{
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("bombCrate"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x/2, textureSize.y/2);

    this->setPosition(192.0f, 192.0f);

    Renderer* renderer = new Renderer("BombProjectile");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);


    this->bombBehaviour = new BombBehaviour("Bomb_Behaviour");
    this->attachComponent(bombBehaviour);

    this->collider = new Collider("BombCollider");

    collider->setLocalBounds(sprite->getGlobalBounds());
    collider->setCollisionListener(this);
    this->attachComponent(collider);

    /*this->movementCollider = new Collider("movementBombCollider");

    movementCollider->setLocalBounds(sprite->getGlobalBounds());
    movementCollider->setCollisionListener(this);
    this->attachComponent(movementCollider);*/
}

void BombObject::onRelease()
{
    PathManager::getInstance()->untrackWallObject(this->collider);
}

void BombObject::onActivate()
{
    Player* player = (Player*)GameObjectManager::getInstance()->findObjectByName("Player");
    sf::Vector2f position = player->getTransformable()->getPosition();

    position = TileMapState::getInstance()->findNearestNeighbor(position);

    this->setPosition(position.x, position.y);
   
    this->hasHit = false;

    PathManager::getInstance()->trackWallObject(this->collider);
    this->collider->setAlreadyCollided(true);
    //PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* BombObject::clone()
{
    APoolable* copyObj = new BombObject(this->name);
    return copyObj;
}

void BombObject::onCollisionEnter(AGameObject* contatct)
{
    /*if (contatct->getName().find("enemy") != string::npos && !this->hasHit) {
        this->hasHit = true;
        GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
        projectilePool->releasePoolable((APoolable*)this);
        cout << "HIT" << endl;
    }*/
}

void BombObject::onCollisionExit(AGameObject* contact)
{
}
