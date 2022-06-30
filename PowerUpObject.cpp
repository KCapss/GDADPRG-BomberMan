#include "PowerUpObject.h"
//#include "Player.h"

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

    this->powerUPType = PlayerState::getInstance()->retrieveActivePowerUPType();

    this->sprite = new sf::Sprite();
    this->setupSprite(powerUPType);

    
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setScale(0.8f, 0.8f);

    
    //Component system
    Renderer* renderer = new Renderer("PowerUPSprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);


   //Collider Setup
    this->collider = new Collider(this->name);

    collider->setLocalBounds(sprite->getGlobalBounds());
    collider->setCollisionListener(this);
    this->attachComponent(collider);
}

void PowerUpObject::onRelease()
{
    
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void PowerUpObject::onActivate()
{
    //RandomizePosition

    this->tempPos = TileMapState::getInstance()->randomizeSpawn("PowerUp");

    this->setPosition(tempPos.x, tempPos.y);

    TileMapState::getInstance()->registerPosition(tempPos, "PowerUp");
    PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* PowerUpObject::clone()
{
    APoolable* copyObj = new PowerUpObject(this->name );
    return copyObj;
}

void PowerUpObject::onCollisionEnter(AGameObject* contact)
{
    if (contact->getName().find("Player") != std::string::npos) {
        cout << "Power up collected" << endl;

        GameObjectPool* powerUPPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POWER_UP_POOL_TAG);
        powerUPPool->releasePoolable((APoolable*)this);
    }




}

void PowerUpObject::onCollisionExit(AGameObject* contact)
{
}

void PowerUpObject::setupSprite(PowerUPType type)
{
    //Categroize the sprite
    if (type == PowerUPType::IncreaseBombCount) {
        //Option 1
        sprite->setTexture(*TextureManager::getInstance()->getTexture("powerUp-1"));
    }

    else if (type == PowerUPType::PowerIncrease) {
        //Option 2
        sprite->setTexture(*TextureManager::getInstance()->getTexture("bombCrate"));
    }

    else  if (type == PowerUPType::IncreasSpeed) {
        //Option 3
        sprite->setTexture(*TextureManager::getInstance()->getTexture("bombCrate"));
    }

    else if (type == PowerUPType::Detonator) {
        //Option 4
        sprite->setTexture(*TextureManager::getInstance()->getTexture("bombCrate"));
    }
}


