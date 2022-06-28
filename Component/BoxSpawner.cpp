#include "BoxSpawner.h"

#include "../ObjectPooling/ObjectPoolHolder.h"
#include "../BoxObject.h"

BoxSpawner::BoxSpawner(int numEnemies, string name, AGameObject* parent) : AComponent(name, Script)
{
	this->boxPool = new GameObjectPool(ObjectPoolHolder::BOX_POOL_TAG,
		new BoxObject("Box"),
		numEnemies,
		parent);
	this->boxPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(this->boxPool);
}

BoxSpawner::~BoxSpawner()
{
}

void BoxSpawner::perform()
{
	GameObjectPool* boxPoolHandler = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BOX_POOL_TAG);
	boxPoolHandler->requestPoolable();
}
