#include "LevelSelectScene.h"
#include "SceneManager.h"
#include "../Screen/LevelSelectScreen.h"

LevelSelectScene::LevelSelectScene() : AScene("LevelSelect")
{
}

LevelSelectScene::~LevelSelectScene()
{
}

void LevelSelectScene::onLoadResources()
{
}

void LevelSelectScene::onLoadObjects()
{
	LevelSelectScreen* levelSelectScreen = new LevelSelectScreen("TitleScreen");
	this->registerObject(levelSelectScreen);
}

void LevelSelectScene::onUnloadResources()
{
}
