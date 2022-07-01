#pragma once
#include "AScene.h"
#include "../ObjectPooling/GameObjectPool.h"

class Level2Scene :
    public AScene
{
public:
    Level2Scene();
    ~Level2Scene();

    void onLoadResources();
    void onLoadObjects();

    void onUnloadResources();

private:
    GameObjectPool* bombPool;
    GameObjectPool* bombVFXPool;
    GameObjectPool* powerUPPool;

};

