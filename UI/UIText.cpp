#include "UIText.h"
#include "../Manager/FontManager.h"
#include "../Component/Renderer.h"

UIText::UIText(string name): AGameObject (name)
{
	this->text = new sf::Text();
}

UIText::~UIText()
{
	AGameObject::~AGameObject();
	//delete this->text;
}

void UIText::initialize()
{
	sf::Font* font = FontManager::getInstance()->getFont("default");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4.0f);

	this->setSize(40);
	this->setText("<Using a PlaceHolder>");

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(text);
	this->attachComponent(renderer);


}

void UIText::setText(string text)
{
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();

	//Allign Center, you can put other allignment here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);

}

string UIText::getText()
{

	return this->text->getString();
}

void UIText::setSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}
