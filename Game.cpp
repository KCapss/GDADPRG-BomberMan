#include "Game.h"
#include <iostream>
#include <string>

#include "EmptyGameObject.h"

#include "TextureManager.h"
#include "Manager/FontManager.h"
#include "Manager/ApplicationManager.h"

#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "EnemyAirplane.h"

#include "Screen/MainMenuScreen.h"
#include "Screen/HUD.h"
#include "Scene/SceneManager.h"

#include "Scene/MainMenuScene.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"


#include "Component/EnemySwarmHandler.h"
#include "Scene/SceneManager.h"

Game::Game() : mWindow(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "Kevin Carl Capalar")
{
	//Generate first all path to the texture needed
	//genPath();
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();
	ApplicationManager::getInstance()->initialize(&mWindow);

	//register scene
	SceneManager::getInstance()->registerScene(new TitleScene());
	SceneManager::getInstance()->registerScene(new GameScene());
	SceneManager::getInstance()->registerScene(new MainMenuScene());

	//load first scene
	//SceneManager::getInstance()->loadScene(GAME_SCENE_NAME);
	SceneManager::getInstance()->loadScene("TitleScene");

	/*
	BGObject* bgObject = new BGObject ("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
	GameObjectManager::getInstance()->addObject(planeObject);

	AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1");
	planeObject->attachChild(support1);
	support1->setPosition(50, 100);

	AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2");
	planeObject->attachChild(support2);
	support2->setPosition(-50, 100);

	HUD* hudMenu = new HUD("HUDMenu");
	GameObjectManager::getInstance()->addObject(hudMenu);

	MainMenuScreen* mainMenu = new MainMenuScreen("MainMenu");
	GameObjectManager::getInstance()->addObject(mainMenu);

	srand(time(NULL));
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(200, "SwarmHandler", enemiesManager);

	enemiesManager->attachComponent(swarmHandler);
	GameObjectManager::getInstance()->addObject(enemiesManager);
	*/


	/*TextureManager::getInstance()->loadAll();
	createEntity("bed_", 0, 0);
	createEntity("bench_", 150, 0);
	createEntity("boxGift_", 300, 0);
	createEntity("coin_", 450, 0);*/

	
	
	

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	float lastTime = 0;
	
	while (mWindow.isOpen())
	{
		processEvent();
		timeSinceLastUpdate += clock.restart();


		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvent();
			update(TimePerFrame);

		}
		render();
		SceneManager::getInstance()->checkLoadScene();
	}
	
}

void Game::processEvent()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {

		switch (event.type) {
		
		case sf::Event::Closed:
			mWindow.close();
			break;

		default:
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
				GameObjectManager::getInstance()->addObject(new EnemyAirplane("EnemyAirplane"));
			}
			GameObjectManager::getInstance()->processInput(event);
			break;

		}

		
			

	}
}


void Game::update(sf::Time deltaTime)
{

	if (!ApplicationManager::getInstance()->isPaused()) {
		GameObjectManager::getInstance()->update(deltaTime);
	}

	//Declare a finder findObject
	/*else {
		(GameObjectManager::getInstance()->findObjectByName("MainMenu")->update(deltaTime));
	}*/
	

	/*
	for (int i = 0; i < this->entityList.size(); i++) {
		entityList[i]->update();
	}
	*/
	//sf::SoundBuffer buffer;
	//sf::Music music;
	//sf::Sound sound;

	/*
	if (!buffer.loadFromFile("Media/Texture/EnemyGunfire.wav")) {
		std::cout << "Error" << std::endl;
	}
	*/
	//sound.setBuffer(buffer);
	//sound.play();
	
}

void Game::render()
{
	mWindow.clear();
	/*
	for (int i = 0; i < this->entityList.size(); i++) {
		//mWindow.draw(*mSampleEntity[i].getSprite());
		mWindow.draw(*entityList[i]->getSprite());
	}
	*/
	GameObjectManager::getInstance()->draw(&mWindow);
	mWindow.display();

	
	

}



void Game::genPath()
{
	this->path.push_back("Media/Texture/bed0000.png");
	this->path.push_back("Media/Texture/bench0000.png");
	this->path.push_back("Media/Texture/boxGift_0000.png");
	this->path.push_back("Media/Texture/coin0000.png");

}






