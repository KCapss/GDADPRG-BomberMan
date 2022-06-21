#include "UIButton.h"
#include "../Component/UIButtonInputController.h"
#include "../Component/Renderer.h"

//Debugger Header
#include <iostream>
using namespace std;

UIButton::UIButton(string name, sf::Texture* normalTexture, sf::Texture* pressedTexture) 
	: AGameObject(name)
{
	this->sprite = new sf::Sprite();
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

UIButton::~UIButton()
{
	AGameObject::~AGameObject();
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);
}

void UIButton::changeButtonToPressed()
{
	this->sprite->setTexture(*this->pressedTexture);
}

sf::FloatRect UIButton::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::getGlobalBounds()
{
	//insertCalculation for localBounds
	sf::FloatRect bounds = this->sprite->getGlobalBounds();
	bounds = this->getGlobalTransform().transformRect(bounds);

	return bounds;
}

void UIButton::setButtonListener(ButtonListener* listener)
{
	//asisgn input controller
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController("UI_InputController", this->listener);
	this->attachComponent(inputController);
}

void UIButton::initialize()
{ 
	
	this->sprite->setTexture(*this->normalTexture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(this->sprite);
	this->attachComponent(renderer);
}


