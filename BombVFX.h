#pragma once
#include "ObjectPooling/APoolable.h"
#include "AGameObject.h"
#include "Physics/PhysicsManager.h"

class BombVFX :
    public APoolable, public CollisionListener
{
public:
    BombVFX(string name);
    ~BombVFX();

    void initialize();
    void onRelease();
    void onActivate();
    APoolable* clone();

    void update(sf::Time deltaTime);

    void onCollisionEnter(AGameObject* contatct);
    void onCollisionExit(AGameObject* contact);
private:
    const float BOMB_DURATION = 0.2f;

    Collider* collider = NULL;
    sf::Vector2f tempPos = sf::Vector2f(0, 0);
    float ticks = 0;

    
};

