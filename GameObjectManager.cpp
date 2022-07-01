#include "GameObjectManager.h"
#include "Manager/ApplicationManager.h"
#include "PlayerState.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (gameObjectMap[name] != NULL) {
		return gameObjectMap[name];
	}
	else {
		//std::cerr << "Object" << name << "not found";
	}

	return nullptr;
}

std::vector<AGameObject*> GameObjectManager::getAllObject()
{
	return gameObjectList;
}

int GameObjectManager::activeObject()
{
	return gameObjectList.size();
}

void GameObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		if (gameObjectList[i] != this->findObjectByName("MainMenu"))
			gameObjectList[i]->processInput(event);

		else if (ApplicationManager::getInstance()->isPaused() && PlayerState::getInstance()->isPlayerAlive())
			this->findObjectByName("MainMenu")->processInput(event);

		else if (ApplicationManager::getInstance()->isPaused() )
			this->findObjectByName("GameOver")->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		if (gameObjectList[i] != this->findObjectByName("MainMenu"))
			gameObjectList[i]->update(deltaTime);

		else if (ApplicationManager::getInstance()->isPaused() && PlayerState::getInstance()->isPlayerAlive())
			this->findObjectByName("MainMenu")->update(deltaTime);

		else if (ApplicationManager::getInstance()->isPaused())
			this->findObjectByName("GameOver")->update(deltaTime);
	}

	if (ApplicationManager::getInstance()->isPaused()) {
		cout << "is Paused" << endl;
	}
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < gameObjectList.size(); i++) {
		if (gameObjectList[i] != this->findObjectByName("MainMenu"))
			gameObjectList[i]->draw(window, sf::RenderStates::Default);

		else if (ApplicationManager::getInstance()->isPaused() && PlayerState::getInstance()->isPlayerAlive())
			this->findObjectByName("MainMenu")->draw(window, sf::RenderStates::Default);

		else if (ApplicationManager::getInstance()->isPaused())
			this->findObjectByName("GameOver")->draw(window, sf::RenderStates::Default);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	gameObjectMap[gameObject->getName()] = gameObject;
	gameObjectList.push_back(gameObject);
	gameObject->initialize();
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->getName();
	delete gameObject;
	gameObjectMap.erase(key);
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject));
	gameObjectList.shrink_to_fit();
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = findObjectByName(name);

	if (object != NULL) {
		deleteObject(object);
	}

}

void GameObjectManager::deleteAllObjectInScene()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		delete this->gameObjectList[i];
	}
	gameObjectMap.clear();
	gameObjectList.clear();
	this->gameObjectList.shrink_to_fit();

}
