#pragma once

#include "ObjectPooling/APoolable.h"
#include "AGameObject.h"

#include "TileMapState.h"
#include "Physics/PhysicsManager.h"
#include "PlayerState.h"



class PowerUpObject :
    public APoolable, public CollisionListener
{
public:
    PowerUpObject(string name);
    ~PowerUpObject();

    void initialize();
    void onRelease();
    void onActivate();
    APoolable* clone();

    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* contact);


    void setupSprite(PowerUPType type);

   
private:
    sf::Vector2f tempPos;
    
    Collider* collider = NULL;
    //Collider* movementCollider = NULL;

    PowerUPType powerUPType;
    bool hasHit = false;

    sf::Vector2f tempPosition = sf::Vector2f(0, 0);
};

