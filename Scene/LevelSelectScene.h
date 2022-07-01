#pragma once
#include "AScene.h"
class LevelSelectScene : public AScene
{
public:
	LevelSelectScene();
	~LevelSelectScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

