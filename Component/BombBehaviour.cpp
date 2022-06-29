#include "BombBehaviour.h"
#include "../AGameObject.h"
#include "../ObjectPooling/ObjectPoolHolder.h"
#include "../TextureManager.h"
BombBehaviour::BombBehaviour(string name): AComponent(name, Script)
{
}

void BombBehaviour::perform()
{
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > 1.0f) {
		reset();
		//Do some action
		GameObjectPool* bombPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
		bombPool->releasePoolable((APoolable*)this->getOwner());

		//RemoveObject

	}
}

void BombBehaviour::reset()
{
	this->ticks = 0.0f;
}
