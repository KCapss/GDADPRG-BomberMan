#pragma once
#include "AScene.h"
#include <unordered_map>
#include <vector>

typedef std::unordered_map<string, AScene*> SceneTable;
typedef std::vector<std::string> SceneList;
const std::string MAIN_MENU_SCENE_NAME = "MainMenuScene";
const std::string GAME_SCENE_NAME = "GameScene";

class SceneManager
{
public:
	

	static SceneManager* getInstance();

	void registerScene(AScene* scene);
	void loadScene(std::string name);
	void checkLoadScene();

	void unloadScene();
	bool isSceneLoaded(std::string name);

private:
	SceneManager() {};
	static SceneManager* sharedInstance;

	SceneTable storedScene;
	//SceneTable activeScene = complex Scene (multiple scene)
	AScene* activeScene = NULL;

	bool isLoading = false;
	std::string toLoadSceneName;
};

