#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::sharedInstance = NULL;

SceneManager* SceneManager::getInstance()
{
    if (sharedInstance == NULL) {
        sharedInstance = new SceneManager();
    }

    return sharedInstance;
}

void SceneManager::registerScene(AScene* scene)
{
    std::cout << scene->getSceneName() << " registered! " << std::endl;
    this->storedScene[scene->getSceneName()] = scene;
}

void SceneManager::loadScene(std::string name)
{
    this->isLoading = true;
    this->toLoadSceneName = name;
}

void SceneManager::checkLoadScene()
{
    if (this->isLoading) {
        this->unloadScene();
        this->activeScene = this->storedScene[this->toLoadSceneName];
        this->activeScene->onLoadResources();
        this->activeScene->onLoadObjects();
        this->isLoading = false;

    }
}

void SceneManager::unloadScene()
{
    if (this->activeScene != NULL) {
        this->activeScene->onUnloadObjects();
        this->activeScene->onUnloadResources();
   }
}

bool SceneManager::isSceneLoaded(std::string name)
{
    return this->activeScene->getSceneName() == name;
}
