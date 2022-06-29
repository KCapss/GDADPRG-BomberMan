#include "GameScene.h"
#include "SceneManager.h"

//All obj
//#include "../BGObject.h"
//#include "../AirplanePlayer.h"
//#include "../AirplaneSupport.h"
//#include "../ProjectileObject.h"

#include "../Player.h"
#include "../WallManager.h"
#include "../BombObject.h"

//All UI
#include "../Screen/HUD.h"
#include "../Screen/MainMenuScreen.h"

//AllComponent
#include "../Component/BoxSpawner.h"


//AllPool
#include "../ObjectPooling/ObjectPoolHolder.h"



#include "../EmptyGameObject.h"
#include "../Physics/PhysicsManager.h"
#include "../Physics/PathManager.h"
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
	//Physics
	EmptyGameObject* physicsManager = new EmptyGameObject("PhysicsManager");
	this->registerObject(physicsManager);
	PhysicsManager::initialize("PhysicsManager", physicsManager);

	//Path
	EmptyGameObject* pathManager = new EmptyGameObject("PathManager");
	this->registerObject(pathManager);
	PathManager::initialize("PathManager", pathManager);

	srand(time(NULL));
	WallManager* walldesign = new WallManager("WallManage");
	GameObjectManager::getInstance()->addObject(walldesign);

	EmptyGameObject* boxManager = new EmptyGameObject("EnemiesManager");
	BoxSpawner* boxSpawner = new BoxSpawner(55, "SwarmHandler", boxManager);

	boxManager->attachComponent(boxSpawner);
	GameObjectManager::getInstance()->addObject(boxManager);

	EmptyGameObject* bombSpawner = new EmptyGameObject("BombSpawner");
	GameObjectManager::getInstance()->addObject(bombSpawner);

	this->bombPool = new GameObjectPool
	(ObjectPoolHolder::PROJECT_POOL_TAG,
		new BombObject("projectile"),
		3,
		bombSpawner);

	this->bombPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(bombPool);


	Player* player = new Player("Player");
	GameObjectManager::getInstance()->addObject(player);
	player->setPosition((64.0f) + 32.0f, (64.0f * 2.f) + 32.0f);
	


	

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

