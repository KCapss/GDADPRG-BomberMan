#include "ObjectPoolHolder.h"

string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";
string ObjectPoolHolder::PROJECT_POOL_TAG = "ProjectilePool";
string ObjectPoolHolder::BOX_POOL_TAG = "BoxPool";
string ObjectPoolHolder::VFX_POOL_TAG = "VFXPool";
string ObjectPoolHolder::POWER_UP_POOL_TAG = "PowerUPPool";

ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
    if (sharedInstance == NULL) {
        sharedInstance = new ObjectPoolHolder();
    }

    return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
    this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
    this->poolMap.erase(pool->getTag());
    delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(string tag)
{
    return this->poolMap[tag];
}
