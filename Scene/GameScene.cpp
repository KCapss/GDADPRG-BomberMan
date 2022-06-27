#include "GameScene.h"
#include "SceneManager.h"

//All obj
//#include "../BGObject.h"
//#include "../AirplanePlayer.h"
//#include "../AirplaneSupport.h"
//#include "../ProjectileObject.h"

#include "../Player.h"
#include "../WallManager.h"

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

	WallManager* walldesign = new WallManager("WallManage");
	GameObjectManager::getInstance()->addObject(walldesign);

	Player* player = new Player("Player");
	GameObjectManager::getInstance()->addObject(player);

	

			
	/*Wall* Tboundaries = new Wall("Wall", Top);
	GameObjectManager::getInstance()->addObject(Tboundaries);

	Wall* Lboundaries = new Wall("Wall", Left);
	GameObjectManager::getInstance()->addObject(Lboundaries);

	Wall* Rboundaries = new Wall("Wall", Right);
	GameObjectManager::getInstance()->addObject(Rboundaries);

	Wall* Bboundaries = new Wall("Wall", Bottom);
	GameObjectManager::getInstance()->addObject(Bboundaries);*/

	

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

