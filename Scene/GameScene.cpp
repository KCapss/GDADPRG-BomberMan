#include "GameScene.h"
#include "SceneManager.h"

//All obj
//#include "../BGObject.h"
//#include "../AirplanePlayer.h"
//#include "../AirplaneSupport.h"
//#include "../ProjectileObject.h"

//All UI
#include "../Screen/HUD.h"
#include "../Screen/MainMenuScreen.h"

//AllComponent

//AllPool
#include "../ObjectPooling/ObjectPoolHolder.h"



#include "../EmptyGameObject.h"
#include "../Physics/PhysicsManager.h"
#include "../GameObjectManager.h"


GameScene::GameScene(): AScene(GAME_SCENE_NAME)
{

}

GameScene::~GameScene()
{
}

void GameScene::onLoadResources()
{
}

void GameScene::onLoadObjects()
{
	EmptyGameObject* physicsManager = new EmptyGameObject("PhysicsManager");
	this->registerObject(physicsManager);
	PhysicsManager::initialize("PhysicsManager", physicsManager);


	srand(time(NULL));
	HUD* hudMenu = new HUD("HUDMenu");
	GameObjectManager::getInstance()->addObject(hudMenu);

	MainMenuScreen* mainMenu = new MainMenuScreen("MainMenu");
	GameObjectManager::getInstance()->addObject(mainMenu);
	

	
}

void GameScene::onUnloadResources()
{
	//GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
	//ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool);
	AScene::onUnloadObjects();
}

