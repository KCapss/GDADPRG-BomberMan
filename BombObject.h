#pragma once
#include "ObjectPooling/APoolable.h"
#include "AGameObject.h"
//#include "Component/ProjectileMovement.h"
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

    void onCollisionEnter(AGameObject* contatct);
    void onCollisionExit(AGameObject* contact);
private:
    //BombObject* bombObject = NULL;
    Collider* collider = NULL;
    Collider* movementCollider = NULL;
    bool hasHit = false;
};

