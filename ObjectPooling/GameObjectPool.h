#pragma once
#include "APoolable.h"

#include <vector>
#include <queue>

typedef std::vector<APoolable*> ObjectList;

class GameObjectPool
{
public:
    GameObjectPool(string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent);
    ~GameObjectPool();
    void initialize();
    bool  hasObjectAvailable(int requestSize);
    APoolable* requestPoolable();
    ObjectList requestPoolableBatch(int size);

    void releasePoolable(APoolable* poolableObject);
    void releasedPoolableBatch(ObjectList objectList);

    string getTag();

    //Additional Function
    void checkFinishedObject();

private:
    string tag;
    APoolable* objectCopy = NULL;
    AGameObject* parent = NULL;
    int maxPoolSize = 20;

    ObjectList availableObjects;
    ObjectList usedObject;

    void setEnabled(APoolable* poolableObject, bool flag);
};

