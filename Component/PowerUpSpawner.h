#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"
class PowerUpSpawner :
    public AComponent
{

public:
    PowerUpSpawner(int numEnemies, string name, string objName, AGameObject* parent);
    ~PowerUpSpawner();
    void perform();

private:

    GameObjectPool* powerUpPool;
    int itemCount = 0;
    int currCount = 0;
};

