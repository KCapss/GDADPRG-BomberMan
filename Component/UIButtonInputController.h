#pragma once
#include "GenericInputController.h"
#include "../UI/ButtonListener.h"
#include <string>

using namespace std;
class UIButtonInputController :
    public GenericInputController
{
public:

    UIButtonInputController(string name, ButtonListener* buttonListener);
    ~UIButtonInputController();

    void perform();

private:
    ButtonListener* buttonListener;
    bool pressed = false;

};

