#pragma once
#include <string> 
#include "../AGameObject.h"

class AScene {
public:
	AScene(std::string sceneName);
	~AScene();

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	//getter

	std::string getSceneName();

protected:
	void registerObject(AGameObject* object);
	std::string sceneName;
};