#pragma once
#include "AGameObject.h"
#include <stddef.h>
#include <unordered_map>
#include <SFML/System.hpp>

class GameObjectManager: sf::NonCopyable
{
public:
	static GameObjectManager* getInstance();
	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllObject();
	
	int activeObject();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);
	void addObject(AGameObject* window);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);

	//New-SceneManager
	void deleteAllObjectInScene();


private:
	GameObjectManager() {};
	static GameObjectManager* sharedInstance;
	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;


};

