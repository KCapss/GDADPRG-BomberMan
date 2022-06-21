#pragma once

#include "GameObjectPool.h"
#include <unordered_map>

typedef std::unordered_map<string, GameObjectPool*> PoolMap;

class ObjectPoolHolder
{
public:

	//pool names
	static string ENEMY_POOL_TAG;

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

