#pragma once
#include "../AGameObject.h"
#include "../UI/UIButton.h"
#include "../UI//UIText.h"
#include "../UI/ButtonListener.h"

class MainMenuScreen :
    public AGameObject, public ButtonListener
{
public:
    MainMenuScreen(string name);
    ~MainMenuScreen();

    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);
private:
    UIText* mainTextL1;
    UIText* mainTextL2;
    
    UIButton* button_1;
    UIText* button_1Text;

    UIButton* button_2;
    UIText* button_2Text;




};

