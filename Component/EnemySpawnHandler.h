#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"
class EnemySpawnHandler :
    public AComponent
{
public:
    EnemySpawnHandler(int numEnemies, string name, AGameObject* parent);
    ~EnemySpawnHandler();
    void perform();

private:

    GameObjectPool* enemyPool;

    const float SPAWN_INTERVAL = 0.01f;
    float ticks = 0.0f;
    int count = 0;
    int maxCount = 0;

};

