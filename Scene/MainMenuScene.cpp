#include "MainMenuScene.h"
#include "../Screen/MainMenuScreen.h"
#include "SceneManager.h"

MainMenuScene::MainMenuScene(): AScene("MainMenuScene")
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::onLoadResources()
{
}

void MainMenuScene::onLoadObjects()
{
	MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
	this->registerObject(menuScreen);

}

void MainMenuScene::onUnloadResources()
{

}
