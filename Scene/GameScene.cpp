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
#include "../BombVFX.h"
#include "../EnemyObject.h"
#include "../Component/EnemySpawnHandler.h"


//All UI
#include "../Screen/HUD.h"
#include "../Screen/MainMenuScreen.h"

//AllComponent
#include "../Component/BoxSpawner.h"


//AllPool
#include "../ObjectPooling/ObjectPoolHolder.h"
#include "../TileMapState.h"


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
	BoxSpawner* boxSpawner = new BoxSpawner(40, "SwarmHandler", boxManager);

	boxManager->attachComponent(boxSpawner);
	GameObjectManager::getInstance()->addObject(boxManager);

	//Bomb
	EmptyGameObject* bombSpawner = new EmptyGameObject("BombSpawner");
	GameObjectManager::getInstance()->addObject(bombSpawner);

		//BombObject
	this->bombPool = new GameObjectPool
	(ObjectPoolHolder::PROJECT_POOL_TAG,
		new BombObject("projectile"),
		10,
		bombSpawner);

	this->bombPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(bombPool);

		//VFX
	EmptyGameObject* VFXBombSpawner = new EmptyGameObject("VFXBombSpawner");
	GameObjectManager::getInstance()->addObject(VFXBombSpawner);

	this->bombVFXPool = new GameObjectPool
	(ObjectPoolHolder::VFX_POOL_TAG,
		new BombVFX("VFX"),
		50,
		VFXBombSpawner);

	this->bombVFXPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(bombVFXPool);


	//Enemy
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemySpawnHandler* enemySpawner = new EnemySpawnHandler(5, "EnemySpawner", enemiesManager);

	enemiesManager->attachComponent(enemySpawner);
	GameObjectManager::getInstance()->addObject(enemiesManager);


	//Player
	Player* player = new Player("Player");
	GameObjectManager::getInstance()->addObject(player);
	player->setPosition((64.0f) + 32.0f, (64.0f * 2.f) + 32.0f);
	


	

	//HUD
	HUD* hudMenu = new HUD("HUDMenu");
	GameObjectManager::getInstance()->addObject(hudMenu);

	MainMenuScreen* mainMenu = new MainMenuScreen("MainMenu");
	GameObjectManager::getInstance()->addObject(mainMenu);
	

	
}

void GameScene::onUnloadResources()
{
	//Unload Pool
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool);

	GameObjectPool* bombPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECT_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(bombPool);

	GameObjectPool* bombVFXPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::VFX_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(bombVFXPool);

	GameObjectPool* boxPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BOX_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(boxPool);

	TileMapState::getInstance()->resetAll();

	AScene::onUnloadObjects();
}

