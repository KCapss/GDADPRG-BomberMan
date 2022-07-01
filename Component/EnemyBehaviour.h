#pragma once
#include "AComponent.h"
class EnemyBehaviour :
    public AComponent
{
    enum Tactics
    {
        Bounce = 0,
        Search = 1
    };

public:
    EnemyBehaviour(string name);
    void perform();
    void reset();

    //Properties
    void changePattern(Tactics tactics);
    void move();

    

private:
    const float timer = 2.5f;
    float ticks = 0.0f;

  

};

