#include "MainMenuScreen.h"
#include "../TextureManager.h"
#include "../Component/Renderer.h"
#include "../Game.h"
#include "../Manager/ApplicationManager.h"
#include "../Scene/SceneManager.h"
#include <iostream>


MainMenuScreen::MainMenuScreen(string name) : AGameObject(name), ButtonListener()
{


}

MainMenuScreen::~MainMenuScreen()
{
	AGameObject::~AGameObject();
}

void MainMenuScreen::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setScale(sf::Vector2f(8.0f, 6.0f));

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->setPosition(Game::GAME_WINDOW_WIDTH / 2, Game::GAME_WINDOW_HEIGHT / 2);

	this->mainTextL1 = new UIText("text_1");
	this->attachChild(this->mainTextL1);
	this->mainTextL1->setPosition(0, -50);
	this->mainTextL1->setSize(50);
	this->mainTextL1->setText("Are you sure you want");

	this->mainTextL2 = new UIText("text_2");
	this->attachChild(this->mainTextL2);
	this->mainTextL2->setPosition(0, 0);
	this->mainTextL2->setSize(50);
	this->mainTextL2->setText("to quit the game?");

	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->button_1 = new UIButton("Yes_btn", btnNormal, btnPressed);
	this->attachChild(this->button_1);
	this->button_1->setPosition(-150, 150);
	this->button_1->getTransformable()->setScale(1.2f, 1.2f);

	this->button_1Text = new UIText("text_1");
	this->button_1->attachChild(this->button_1Text);
	this->button_1Text->setPosition(0, 0);
	this->button_1Text->setSize(30);
	this->button_1Text->setText("YES");
	this->button_1->setButtonListener(this);

	this->button_2 = new UIButton("No_btn", btnNormal, btnPressed);
	this->attachChild(this->button_2);
	this->button_2->setPosition(150, 150);
	this->button_2->getTransformable()->setScale(1.2f, 1.2f);

	this->button_2Text = new UIText("text_2");
	this->button_2->attachChild(this->button_2Text);
	this->button_2Text->setPosition(0, 0);
	this->button_2Text->setSize(30);
	this->button_2Text->setText("NO");
	this->button_2->setButtonListener(this);


}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	//Veryfy Button Click
	/*std::cout << button->getName()  ;*/
	if (button->getName() == "Yes_btn") {
		ApplicationManager::getInstance()->resumeApplication();
		SceneManager::getInstance()->loadScene("TitleScene");
	}
		

	else if (button->getName() == "No_btn")
		ApplicationManager::getInstance()->resumeApplication();
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	//Veryfy Button Click
	//std::cout << button->getName();
}
