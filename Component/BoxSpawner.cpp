#include "BoxSpawner.h"
#include "../PowerUpObject.h"

#include "../ObjectPooling/ObjectPoolHolder.h"
#include "../BoxObject.h"

BoxSpawner::BoxSpawner(int numEnemies, string name, AGameObject* parent) : AComponent(name, Script)
{
	
	//Before the Box Start
	this->boxPool = new GameObjectPool(ObjectPoolHolder::BOX_POOL_TAG,
		new BoxObject("Box"),
		numEnemies,
		parent);
	this->boxPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(this->boxPool);

	this->boxCount = numEnemies;
}

BoxSpawner::~BoxSpawner()
{
}

void BoxSpawner::perform()
{
	if (boxCount > currCount) {
		GameObjectPool* boxPoolHandler = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BOX_POOL_TAG);
		//boxPoolHandler->requestPoolable();
		boxPoolHandler->requestPoolableBatch(boxCount);

		//currCount++;
		currCount += boxCount;
	}
	
}
