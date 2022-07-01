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
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bar"));

	this->sprite->setTextureRect(sf::IntRect(0, 0, (17 * 64), (14* 64)));


	sf::Vector2u textureSize = sf::Vector2u(sprite->getTextureRect().width, sprite->getTextureRect().height);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("TitleScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->setPosition(Game::GAME_WINDOW_WIDTH / 2, Game::GAME_WINDOW_HEIGHT / 2);


	//Title Name
	this->titleNameTxt1 = new UIText("TitleNameTxt1");
	this->attachChild(this->titleNameTxt1);
	this->titleNameTxt1->setPosition(0, -350);
	this->titleNameTxt1->setSize(200);
	this->titleNameTxt1->setText("BOMBER");

	this->titleNameTxt2 = new UIText("TitleNameTxt2");
	this->attachChild(this->titleNameTxt2);
	this->titleNameTxt2->setPosition(0, -150);
	this->titleNameTxt2->setSize(200);
	this->titleNameTxt2->setText("MAN");

	//Author
	this->authorText = new UIText("AuthorText");
	this->attachChild(this->authorText);
	this->authorText->setPosition(400, 400);
	this->authorText->setSize(15);
	this->authorText->setText("Made By Kevin Carl Capalar");


	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->playBtn = new UIButton("Play_btn", btnNormal, btnPressed);
	this->attachChild(this->playBtn);
	this->playBtn->setPosition(0, Game::GAME_WINDOW_WIDTH / 8);
	this->playBtn->getTransformable()->setScale(1.6f, 1.6f);

	this->playTxt = new UIText("text_1");
	this->playBtn->attachChild(this->playTxt);
	this->playTxt->setPosition(0, -10);
	this->playTxt->setSize(30);
	this->playTxt->setText("Play");
	this->playBtn->setButtonListener(this);

	this->levelBtn = new UIButton("level_Btn", btnNormal, btnPressed);
	this->attachChild(this->levelBtn);
	this->levelBtn->setPosition(0, Game::GAME_WINDOW_WIDTH / 4.5f);
	this->levelBtn->getTransformable()->setScale(1.6f, 1.6f);

	this->levelTxt = new UIText("text_2");
	this->levelBtn->attachChild(this->levelTxt);
	this->levelTxt->setPosition(1, -5);
	this->levelTxt->setSize(20);
	this->levelTxt->setText("Level Select");
	this->levelBtn->setButtonListener(this);


	this->quitBtn = new UIButton("quit_btn", btnNormal, btnPressed);
	this->attachChild(this->quitBtn);
	this->quitBtn->setPosition(0, Game::GAME_WINDOW_WIDTH / 3.f);
	this->quitBtn->getTransformable()->setScale(1.6f, 1.6f);

	this->quitTxt = new UIText("text_2");
	this->quitBtn->attachChild(this->quitTxt);
	this->quitTxt->setPosition(0, -10);
	this->quitTxt->setSize(30);
	this->quitTxt->setText("Quit");
	this->quitBtn->setButtonListener(this);

}

void TitleScreen::onButtonClick(UIButton* button)
{
	if (button->getName() == "Play_btn")
		SceneManager::getInstance()->loadScene("Level_1");
	else if (button->getName() == "level_Btn")
		SceneManager::getInstance()->loadScene("LevelSelect");
	else if (button->getName() == "quit_btn")
		ApplicationManager::getInstance()->applicationQuit();

		
}

void TitleScreen::onButtonReleased(UIButton* button)
{
}
