#include "EnemySpawnHandler.h"

#include "../ObjectPooling/ObjectPoolHolder.h"
#include "../EnemyObject.h"
#include "../PlayerState.h"

EnemySpawnHandler::EnemySpawnHandler(int numEnemies, string name, AGameObject* parent): AComponent(name, Script)
{
	this->enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_POOL_TAG,
		new EnemyObject("enemy"),
		numEnemies,
		parent);
	this->enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(this->enemyPool);

	this->maxCount = numEnemies;
}

EnemySpawnHandler::~EnemySpawnHandler()
{
	//Empty
}

void EnemySpawnHandler::perform()
{
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);	
	if (maxCount > count) {
		enemyPool->requestPoolable();
		count++;
	}
	
	
}
