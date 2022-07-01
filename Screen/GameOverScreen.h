#pragma once
#include "../AGameObject.h"
#include "../UI/UIButton.h"
#include "../UI//UIText.h"
#include "../UI/ButtonListener.h"
class GameOverScreen :
    public AGameObject, public ButtonListener
{
public:
    GameOverScreen(string name);
    ~GameOverScreen();
    void initialize();

    void update(sf::Time deltaTime);

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);

private:
    //Button
    UIButton* resetLevelBtn;
    UIText* resetLevelTxt;


    //Author Name
    UIText* dialogueTxt;

};

