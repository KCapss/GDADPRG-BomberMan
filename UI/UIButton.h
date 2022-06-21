#pragma once
#include "../AGameObject.h"
#include "ButtonListener.h"

class UIButton :
    public AGameObject
{
public:
    UIButton(string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
    ~UIButton();
    void changeButtonToNormal();
    void changeButtonToPressed();
    sf::FloatRect getLocalBounds();
    sf::FloatRect getGlobalBounds();
    void setButtonListener(ButtonListener* listener);

    void initialize();

    //Getters and setters
  



protected:

    sf::Texture* normalTexture;
    sf::Texture* pressedTexture;
    sf::Sprite* sprite;
    ButtonListener* listener;
};

