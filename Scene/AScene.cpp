#include "AScene.h"
#include "../GameObjectManager.h"

AScene::AScene(std::string sceneName) {
	this->sceneName = sceneName;
}

AScene::~AScene() {

}

void AScene::onUnloadObjects() {
	GameObjectManager::getInstance()->deleteAllObjectInScene();
}

std::string AScene::getSceneName()
{
	return this->sceneName;
}

void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}

