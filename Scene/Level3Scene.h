#pragma once
#include "AScene.h"
#include "../ObjectPooling/GameObjectPool.h"

class Level3Scene :
    public AScene
{
public:
    Level3Scene();
    ~Level3Scene();

    void onLoadResources();
    void onLoadObjects();

    void onUnloadResources();

private:
    GameObjectPool* bombPool;
    GameObjectPool* bombVFXPool;
    GameObjectPool* powerUPPool;

};

