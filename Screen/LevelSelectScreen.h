#pragma once
#include "../AGameObject.h"
#include "../UI/UIButton.h"
#include "../UI//UIText.h"
#include "../UI/ButtonListener.h"
class LevelSelectScreen :
    public AGameObject, public ButtonListener
{
public:
    LevelSelectScreen(string name);
    ~LevelSelectScreen();
    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);

private:
    //Button
    UIButton* lvl1Btn;
    UIText* lvl1Txt;

    UIButton* lvl2Btn;
    UIText* lvl2Txt;

    UIButton* lvl3Btn;
    UIText* lvl3Txt;

    UIButton* backBtn;
    UIText* backTxt;

    //Title Name
    UIText* titleNameTxt1;
    UIText* titleNameTxt2;
};

