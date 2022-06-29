#pragma once
#include "AGameObject.h"
#include "ObjectPooling/APoolable.h"
#include"Physics/CollisionListener.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PathManager.h"

class BoxObject :
    public APoolable, public CollisionListener
{
public:
    BoxObject(std::string name);
    void initialize();

    void onRelease();
    void onActivate();

    APoolable* clone();

    //Collision
    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* gameObject);

private:
    int counter = 0;

    Collider* collider;
};

