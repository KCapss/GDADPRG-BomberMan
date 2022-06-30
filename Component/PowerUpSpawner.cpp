#include "PowerUpSpawner.h"
#include "../PowerUpObject.h"
#include "../ObjectPooling/ObjectPoolHolder.h"

PowerUpSpawner::PowerUpSpawner(int numEnemies, string name, string objName, AGameObject* parent) : AComponent(name, Script)
{
	//Before the Box Start
	this->powerUpPool = new GameObjectPool(ObjectPoolHolder::POWER_UP_POOL_TAG,
		new PowerUpObject(objName),
		numEnemies,
		parent);
	this->powerUpPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(this->powerUpPool);

	this->itemCount = numEnemies;
}

PowerUpSpawner::~PowerUpSpawner()
{
}

void PowerUpSpawner::perform()
{
	if (itemCount > currCount) {
		GameObjectPool* powerUpPoolHandler = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POWER_UP_POOL_TAG);
		//boxPoolHandler->requestPoolable();
		
		powerUpPoolHandler->requestPoolable();
		//currCount++;
		currCount ++;
	}
}
