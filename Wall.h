#pragma once
#include "AGameObject.h"

enum WallTypes {
    Top = 0,
    Bottom = 1,
    Left = 2,
    Right = 3,
    Center = 4,
    Ground = 5,
};

class Wall :
    public AGameObject
{
public:
    Wall(std::string name, WallTypes wallType);
    void initialize();
    void initialPos(sf::Vector2f pos);

private:
    WallTypes wallType = WallTypes::Top;

};

