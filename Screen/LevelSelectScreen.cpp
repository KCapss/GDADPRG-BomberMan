#include "LevelSelectScreen.h"

#include "../Scene/SceneManager.h"
#include "../Scene/MainMenuScene.h"
#include "../TextureManager.h"
#include "../Game.h"
#include "../Component/Renderer.h"
#include "../Manager/ApplicationManager.h"

LevelSelectScreen::LevelSelectScreen(string name) : AGameObject(name), ButtonListener()
{
}

LevelSelectScreen::~LevelSelectScreen()
{
	AGameObject::~AGameObject();
}

void LevelSelectScreen::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bar"));

	this->sprite->setTextureRect(sf::IntRect(0, 0, (17 * 64), (14 * 64)));


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
	this->titleNameTxt1->setSize(125);
	this->titleNameTxt1->setText("Level Select");




	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->lvl1Btn = new UIButton("Lvl1Btn", btnNormal, btnPressed);
	this->attachChild(this->lvl1Btn);
	this->lvl1Btn->setPosition(-300, -50);
	this->lvl1Btn->getTransformable()->setScale(1.6f, 1.6f);

	this->lvl1Txt = new UIText("text_1");
	this->lvl1Btn->attachChild(this->lvl1Txt);
	this->lvl1Txt->setPosition(0, -10);
	this->lvl1Txt->setSize(30);
	this->lvl1Txt->setText("Level 1");
	this->lvl1Btn->setButtonListener(this);

	this->lvl2Btn = new UIButton("Lvl2Btn", btnNormal, btnPressed);
	this->attachChild(this->lvl2Btn);
	this->lvl2Btn->setPosition(0, -50);
	this->lvl2Btn->getTransformable()->setScale(1.6f, 1.6f);

	this->lvl2Txt = new UIText("text_2");
	this->lvl2Btn->attachChild(this->lvl2Txt);
	this->lvl2Txt->setPosition(0, -10);
	this->lvl2Txt->setSize(30);
	this->lvl2Txt->setText("Level 2");
	this->lvl2Btn->setButtonListener(this);


	this->lvl3Btn = new UIButton("Lvl3Btn", btnNormal, btnPressed);
	this->attachChild(this->lvl3Btn);
	this->lvl3Btn->setPosition(300, -50);
	this->lvl3Btn->getTransformable()->setScale(1.6f, 1.6f);

	this->lvl3Txt = new UIText("text_3");
	this->lvl3Btn->attachChild(this->lvl3Txt);
	this->lvl3Txt->setPosition(0, -10);
	this->lvl3Txt->setSize(30);
	this->lvl3Txt->setText("Level 3");
	this->lvl3Btn->setButtonListener(this);

	this->backBtn = new UIButton("BackBtn", btnNormal, btnPressed);
	this->attachChild(this->backBtn);
	this->backBtn->setPosition(-300, 350);
	this->backBtn->getTransformable()->setScale(1.6f, 1.6f);

	this->backTxt = new UIText("text_4");
	this->backBtn->attachChild(this->backTxt);
	this->backTxt->setPosition(0, -10);
	this->backTxt->setSize(30);
	this->backTxt->setText("Back");
	this->backBtn->setButtonListener(this);

}

void LevelSelectScreen::onButtonClick(UIButton* button)
{
	if (button->getName() == "Lvl1Btn")
		SceneManager::getInstance()->loadScene("Level_1");
	else if (button->getName() == "Lvl2Btn")
		SceneManager::getInstance()->loadScene("Level_2");
	else if (button->getName() == "Lvl3Btn")
		SceneManager::getInstance()->loadScene("Level_3");
	else if (button->getName() == "BackBtn")
		SceneManager::getInstance()->loadScene("TitleScene");



}

void LevelSelectScreen::onButtonReleased(UIButton* button)
{
}
