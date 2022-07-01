#include "HUD.h"
#include "../TextureManager.h"
#include "../Component/Renderer.h"
#include "../Game.h"
#include "../Manager/ApplicationManager.h"
#include "../PlayerState.h"

#include <iostream>
using namespace std;

HUD::HUD(string name) : AGameObject(name), ButtonListener()
{
	this->time = 240;
}

HUD::~HUD()
{
	AGameObject::~AGameObject();
}

void HUD::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bar"));

	this->sprite->setTextureRect(sf::IntRect(0, 0, (17 * 64), 64));


	sf::Vector2u textureSize = sf::Vector2u(sprite->getTextureRect().width, sprite->getTextureRect().height);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("HUDScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float gameWidth = Game::GAME_WINDOW_WIDTH;
	float gameHeight = Game::GAME_WINDOW_HEIGHT;

	this->setPosition(gameWidth - textureSize.x/2.0f, textureSize.y/2.0f);
	

	//Button Rendering
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	this->button_1 = new UIButton("Quit_btn", btnNormal, btnPressed);
	this->attachChild(this->button_1);
	this->button_1->setPosition(470, 832);
	this->button_1->getTransformable()->setScale(0.75f, 0.75f);

	this->button_1Text = new UIText("text_1");
	this->button_1->attachChild(this->button_1Text);
	this->button_1Text->setPosition(0, -5);
	this->button_1Text->setSize(30);
	this->button_1Text->setText("QUIT");
	this->button_1->setButtonListener(this);

	//Display Interface
	
	this->Score_Text = new UIText("Score_Txt");
	this->attachChild(this->Score_Text);
	this->Score_Text->setPosition(-420, -10);
	this->Score_Text->setSize(30);
	this->Score_Text->setText("Score: " + to_string(Score));

	this->enemRemain_Text = new UIText("EnemRemain_Text");
	this->attachChild(this->enemRemain_Text);
	this->enemRemain_Text->setPosition(440, -10);
	this->enemRemain_Text->setSize(30);
	this->enemRemain_Text->setText("Remain: " + to_string(remain));

	this->time_Text = new UIText("Time_Text");
	this->attachChild(this->time_Text);
	this->time_Text->setPosition(-30, -10);
	this->time_Text->setSize(30);
	this->time_Text->setText("Time: " + to_string(0));


	/*UIText* time_Text;
	UIText* enemRemain_Text;
	UIText* Score_Text;*/


	
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

void HUD::update(sf::Time deltaTime)
{
	time -= deltaTime.asSeconds();
	Score = PlayerState::getInstance()->retrieveScore();
	remain = PlayerState::getInstance()->retrieveEnemCount();

	this->Score_Text->setText("Score: " + to_string(Score));
	this->enemRemain_Text->setText("Remain: " + to_string(remain));
	this->time_Text->setText("Time: " + to_string((int)time));

}
