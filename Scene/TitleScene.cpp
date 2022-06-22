#include "TitleScene.h"
#include "SceneManager.h"
#include "../Screen/TitleScreen.h"

TitleScene::TitleScene(): AScene("TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::onLoadResources()
{
}

void TitleScene::onLoadObjects()
{
	TitleScreen* titleScreen = new TitleScreen("TitleScreen");
	this->registerObject(titleScreen);
}

void TitleScene::onUnloadResources()
{
}
