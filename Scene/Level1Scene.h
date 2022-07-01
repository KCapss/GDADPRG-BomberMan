#pragma once
#include "AScene.h"
#include "../ObjectPooling/GameObjectPool.h"

class Level1Scene :
    public AScene
{
public:
    Level1Scene();
    ~Level1Scene();

    void onLoadResources();
    void onLoadObjects();

    void onUnloadResources();

private:
    GameObjectPool* bombPool;
    GameObjectPool* bombVFXPool;
    GameObjectPool* powerUPPool;

};

