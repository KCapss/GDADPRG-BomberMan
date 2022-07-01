#pragma once

#include "GameObjectPool.h"
#include <unordered_map>

typedef std::unordered_map<string, GameObjectPool*> PoolMap;

class ObjectPoolHolder
{
public:

	//pool names
	static string ENEMY_POOL_TAG;
	static string PROJECT_POOL_TAG;
	static string BOX_POOL_TAG;
	static string VFX_POOL_TAG;
	static string POWER_UP_POOL_TAG;

	static ObjectPoolHolder* getInstance();

	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(string tag);

private:
	ObjectPoolHolder() {};
	ObjectPoolHolder(ObjectPoolHolder const&) {};
	ObjectPoolHolder& operator=(ObjectPoolHolder const&) {};
	static ObjectPoolHolder* sharedInstance;

	PoolMap poolMap;

};

