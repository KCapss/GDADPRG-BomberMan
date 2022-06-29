#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"

class BombBehaviour: public AComponent
{
public:
    BombBehaviour(string name);
    void perform();
    void reset();

private:
    const float timer = 3.0f;
    float ticks = 0.0f;

    GameObjectPool* bombVFXPool;
};

