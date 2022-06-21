#pragma once
#include "../AGameObject.h"
#include "../UI/UIButton.h"
#include "../UI//UIText.h"
#include "../UI/ButtonListener.h"

class TitleScreen: public AGameObject, public ButtonListener
{
public:
    TitleScreen(string name);
    ~TitleScreen();
    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);

private:
    UIButton* playBtn;
    UIText* playTxt;

    UIButton* quitBtn;
    UIText* quitTxt;

};

