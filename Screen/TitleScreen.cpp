#include "TitleScreen.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MainMenuScene.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../Component/Renderer.h"
#include "../Manager/ApplicationManager.h"

TitleScreen::TitleScreen(string name): AGameObject(name), ButtonListener()
{
}

TitleScreen::~TitleScreen()
{
	AGameObject::~AGameObject();
}

void TitleScreen::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("TitleScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->setPosition(Game::GAME_WINDOW_WIDTH / 2, Game::GAME_WINDOW_HEIGHT / 2);


	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->playBtn = new UIButton("Play_btn", btnNormal, btnPressed);
	this->attachChild(this->playBtn);
	this->playBtn->setPosition(0, -50);
	this->playBtn->getTransformable()->setScale(0.3f, 0.3f);

	this->playTxt = new UIText("text_1");
	this->playBtn->attachChild(this->playTxt);
	this->playTxt->setPosition(0, -20);
	this->playTxt->setSize(100);
	this->playTxt->setText("Play");
	this->playBtn->setButtonListener(this);

	this->quitBtn = new UIButton("quit_btn", btnNormal, btnPressed);
	this->attachChild(this->quitBtn);
	this->quitBtn->setPosition(0, 50);
	this->quitBtn->getTransformable()->setScale(0.3f, 0.3f);

	this->quitTxt = new UIText("text_2");
	this->quitBtn->attachChild(this->quitTxt);
	this->quitTxt->setPosition(0, -20);
	this->quitTxt->setSize(100);
	this->quitTxt->setText("Quit");
	this->quitBtn->setButtonListener(this);
}

void TitleScreen::onButtonClick(UIButton* button)
{
	if (button->getName() == "Play_btn")
		SceneManager::getInstance()->loadScene(GAME_SCENE_NAME);
	else if (button->getName() == "quit_btn")
		ApplicationManager::getInstance()->applicationQuit();

		
}

void TitleScreen::onButtonReleased(UIButton* button)
{
}
