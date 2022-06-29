#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"
class BoxSpawner :
    public AComponent
{
public:
    BoxSpawner(int numEnemies, string name, AGameObject* parent);
    ~BoxSpawner();
    void perform();

private:

    GameObjectPool* boxPool;
    int boxCount = 0;
    int currCount = 0;
};

