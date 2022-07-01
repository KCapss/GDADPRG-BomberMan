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

    //create updateFunction
    void update(sf::Time deltaTime);
    
private:
    //Button
    UIButton* button_1;
    UIText* button_1Text;

    //Display
    UIText* time_Text;
    UIText* enemRemain_Text;
    UIText* Score_Text;

    float time;
    int remain = 0;
    int Score = 0;

    //Variable
    


};

