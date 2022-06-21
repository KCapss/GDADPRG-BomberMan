#include "HUD.h"
#include "../TextureManager.h"
#include "../Component/Renderer.h"
#include "../Game.h"
#include "../Manager/ApplicationManager.h"

#include <iostream>
using namespace std;

HUD::HUD(string name) : AGameObject(name), ButtonListener()
{
}

HUD::~HUD()
{
	AGameObject::~AGameObject();
}

void HUD::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bar"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	//setRect

	Renderer* renderer = new Renderer("HUDScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float gameWidth = Game::GAME_WINDOW_WIDTH;
	float gameHeight = Game::GAME_WINDOW_HEIGHT;

	this->setPosition(gameWidth - textureSize.x/1.9f, gameHeight - textureSize.y/1.5f);
	//this->setPosition(Game::GAME_WINDOW_WIDTH / 2, Game::GAME_WINDOW_HEIGHT / 2);

	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->button_1 = new UIButton("Quit_btn", btnNormal, btnPressed);
	this->attachChild(this->button_1);
	this->button_1->setPosition(150, 0);
	this->button_1->getTransformable()->setScale(0.2f, 0.2f);

	this->button_1Text = new UIText("text_1");
	this->button_1->attachChild(this->button_1Text);
	this->button_1Text->setPosition(0, -20);
	this->button_1Text->setSize(100);
	this->button_1Text->setText("QUIT");
	this->button_1->setButtonListener(this);
}

void HUD::onButtonClick(UIButton* button)
{
	//Veryfy Button Click
	//cout << button->getName() << endl;;
	if (this->button_1->getName() == "Quit_btn")
		ApplicationManager::getInstance()->pauseApplication();
}

void HUD::onButtonReleased(UIButton* button)
{
	//Veryfy Button Click
	//std::cout << button->getName();
}
