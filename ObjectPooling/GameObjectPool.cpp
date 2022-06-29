#include "GameObjectPool.h"
#include <iostream>
#include "../GameObjectManager.h"

GameObjectPool::GameObjectPool(string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;


}

GameObjectPool::~GameObjectPool()
{
	delete this->objectCopy;
	this->objectCopy = NULL;
	this->parent = NULL;
}

void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++) {
		APoolable* poolableObject = this->objectCopy->clone();

		if (this->parent != NULL) {
			this->parent->attachChild(poolableObject);
		}
		else {
			GameObjectManager::getInstance()->addObject(poolableObject);
		}

		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}

APoolable* GameObjectPool::requestPoolable()
{
	if (this->hasObjectAvailable(1)) {
		APoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
		this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
		this->usedObject.push_back(poolableObject);

		//std::cout << "Requested object. Available: " << this->availableObjects.size() << " Used: " << this->usedObject.size() << "\n";
		this->setEnabled(poolableObject, true);
		return poolableObject;
	}

	else {
		std::cout << " No more poolable " + this->objectCopy->getName() + " available! \n";
		checkFinishedObject();
		return NULL;
	}
}

ObjectList GameObjectPool::requestPoolableBatch(int size)
{
	ObjectList returnList;
	if (this->hasObjectAvailable(size)) {
		for (int i = 0; i < size; i++) {
			returnList.push_back(this->requestPoolable());
		}
	}
	else {
		std::cout << "Insufficient " + this->objectCopy->getName() + " available in pool. Count is: " << this->availableObjects.size() <<
			" while requested is " << size << "!\n";
		
	}
	return returnList;
}

void GameObjectPool::releasePoolable(APoolable* poolableObject)
{
	ObjectList::iterator it;

	it = find(usedObject.begin(), usedObject.end(), poolableObject);
	if (it != usedObject.end()) {

		int index = std::distance(usedObject.begin(), it);
		
		this->setEnabled(poolableObject, false);
		this->availableObjects.push_back(poolableObject);

		this->usedObject.erase(this->usedObject.begin() + index);
		this->usedObject.shrink_to_fit();
	}
	
	
}

void GameObjectPool::releasedPoolableBatch(ObjectList objectList)
{
	int releaseCount = objectList.size() - this->availableObjects.size();
	for (int i = 0; i < releaseCount; i++) {
		this->releasePoolable(objectList[i]);
	}
}

string GameObjectPool::getTag()
{
	return this->tag;
}

void GameObjectPool::checkFinishedObject()
{
	for (int i = 0; i < usedObject.size(); i++) {
		if (!usedObject[i]->isEnabled()) {
			releasePoolable(usedObject[i]);
		}
	}
}

void GameObjectPool::setEnabled(APoolable* poolableObject, bool flag)
{
	if (flag) {
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}
	else {
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}
