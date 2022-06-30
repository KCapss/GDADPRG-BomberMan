#pragma once
#include "ObjectPooling/APoolable.h"
#include "Physics/PhysicsManager.h"
#include "Player.h"

class EnemyObject :
    public APoolable, public CollisionListener
{
public:
    EnemyObject(std::string name);
    void initialize();

    void onRelease();
    void onActivate();

    APoolable* clone();

    //Collision
    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* gameObject);

    //Getter
    float retrieveSpeed();
    ObjectFacing retrieveEnemOrientation();
    int getIQ();

    //Setter
    void changeOrientation(ObjectFacing enemOrientation);

private:
    const float ENEM_SPEED_MULLTIPLIER = 200.0f;
    ObjectFacing enemFacing = inCenter;
    int IQ = 2;

    sf::Vector2f tempPos = sf::Vector2f(0,0);

    bool hasHit = false;
    Collider* collider;
};

