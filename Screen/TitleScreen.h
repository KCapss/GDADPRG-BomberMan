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
    //Button
    UIButton* playBtn;
    UIText* playTxt;

    UIButton* levelBtn;
    UIText* levelTxt;

    UIButton* quitBtn;
    UIText* quitTxt;
    
    //Title Name
    UIText* titleNameTxt1;
    UIText* titleNameTxt2;

    //Author Name
    UIText* authorText;

};

