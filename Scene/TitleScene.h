#pragma once
#include "AScene.h"
class TitleScene: public AScene
{
public:
	TitleScene();
	~TitleScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

