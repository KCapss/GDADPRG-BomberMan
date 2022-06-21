#pragma once
#include "../AGameObject.h"
#include "../UI/ButtonListener.h"
#include "../UI/UIButton.h"
#include "../UI/UIText.h"

#include <string>
using namespace std;

class HUD :
    public AGameObject, public ButtonListener
{
public:
    HUD(string name);
    ~HUD();

    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);
private:
    UIButton* button_1;
    UIText* button_1Text;

};

