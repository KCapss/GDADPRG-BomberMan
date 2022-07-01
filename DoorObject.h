#pragma once
#include "AGameObject.h"
#include "Physics/PathManager.h"
#include "Physics/PhysicsManager.h"

class DoorObject :
    public AGameObject, public CollisionListener
{
public:
    DoorObject(std::string name);
    ~DoorObject();
    void initialize();

    //Collision
    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* gameObject);

private:
    Collider* collider;
    sf::Vector2f tempPos;
    
};

