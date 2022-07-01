#include "GameOverScreen.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MainMenuScene.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../Component/Renderer.h"
#include "../Manager/ApplicationManager.h"
#include "../TileMapState.h"
#include "../PlayerState.h"
#include "../Manager/ApplicationManager.h"

#include <iostream>

GameOverScreen::GameOverScreen(string name): AGameObject(name), ButtonListener()
{
}

GameOverScreen::~GameOverScreen()
{
	AGameObject::~AGameObject();
}

void GameOverScreen::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bar"));

	this->sprite->setTextureRect(sf::IntRect(0, 0, (8 * 64), (5 * 64)));


	sf::Vector2u textureSize = sf::Vector2u(sprite->getTextureRect().width, sprite->getTextureRect().height);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(Game::GAME_WINDOW_WIDTH/2, Game::GAME_WINDOW_HEIGHT/2);

	Renderer* renderer = new Renderer("TitleScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	//Title Name
	this->dialogueTxt = new UIText("DialogueTxt");
	this->attachChild(this->dialogueTxt);
	this->dialogueTxt->setPosition(0, -100);
	this->dialogueTxt->setSize(60);
	this->dialogueTxt->setText("GAME OVER");

	//Create Buttonsf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->resetLevelBtn = new UIButton("ResetLevel_Btn", btnNormal, btnPressed);
	this->attachChild(this->resetLevelBtn);
	this->resetLevelBtn->setPosition(0, 100);
	this->resetLevelBtn->getTransformable()->setScale(1.3f, 1.3f);

	this->resetLevelTxt = new UIText("ResetLevelTxt");
	this->resetLevelBtn->attachChild(this->resetLevelTxt);
	this->resetLevelTxt->setPosition(0, 0);
	this->resetLevelTxt->setSize(20);
	this->resetLevelTxt->setText("Reset Level");
	this->resetLevelBtn->setButtonListener(this);

	this->setEnabled(false);
}

void GameOverScreen::update(sf::Time deltaTime)
{
	
	if (!PlayerState::getInstance()->isPlayerAlive()) {
		this->setEnabled(true);
		ApplicationManager::getInstance()->pauseApplication();
	}
}

void GameOverScreen::onButtonClick(UIButton* button)
{
	if (button->getName() == "ResetLevel_Btn") {
		//std::cout << "Level Reset" << std::endl;
		SceneManager::getInstance()->loadScene(
			TileMapState::getInstance()->retrieveActiveScene()
		);
		ApplicationManager::getInstance()->resumeApplication();
		PlayerState::getInstance()->resetLevel();
	}

		
}

void GameOverScreen::onButtonReleased(UIButton* button)
{
}
