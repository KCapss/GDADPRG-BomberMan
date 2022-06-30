#pragma once
#include "ObjectPooling/APoolable.h"
#include "AGameObject.h"
#include "Component/BombBehaviour.h"
#include "Physics/PhysicsManager.h"
class BombObject :
    public APoolable, CollisionListener
{
public:
    BombObject(string name);
    ~BombObject();

    void initialize();
    void onRelease();
    void onActivate();
    APoolable* clone();

    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* contact);

    bool hitConfirmed();
    void resetHit();
private:

    BombBehaviour* bombBehaviour = NULL;
    Collider* collider = NULL;
    //Collider* movementCollider = NULL;


    bool hasHit = false;

    sf::Vector2f tempPosition = sf::Vector2f (0, 0);
};

