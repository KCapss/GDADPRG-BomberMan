#pragma once
#include "AScene.h"
#include "../ObjectPooling/GameObjectPool.h"


class GameScene :
    public AScene
{
public:
    GameScene();
    ~GameScene();

    void onLoadResources();
    void onLoadObjects();

    void onUnloadResources();
   
private:
    GameObjectPool* projectilePool;

};

