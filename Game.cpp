#include "Game.h"
#include <iostream>
#include <string>

#include "EmptyGameObject.h"

#include "TextureManager.h"
#include "Manager/FontManager.h"
#include "Manager/ApplicationManager.h"
#include "TileMapState.h"


#include "Screen/MainMenuScreen.h"
#include "Screen/HUD.h"
#include "Scene/SceneManager.h"

#include "Scene/MainMenuScene.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"

#include "Scene/SceneManager.h"

Game::Game() : mWindow(sf::VideoMode(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT), "Kevin Carl Capalar")
{
	//Generate first all path to the texture needed
	//genPath();
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();
	ApplicationManager::getInstance()->initialize(&mWindow);
	TileMapState::getInstance()->loadAll();

	//register scene
	SceneManager::getInstance()->registerScene(new TitleScene());
	SceneManager::getInstance()->registerScene(new GameScene());
	SceneManager::getInstance()->registerScene(new MainMenuScene());

	//load first scene
	//SceneManager::getInstance()->loadScene(GAME_SCENE_NAME);
	SceneManager::getInstance()->loadScene("GameScene");
	
	
	

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









