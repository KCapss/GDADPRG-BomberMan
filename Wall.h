#pragma once
#include "AGameObject.h"
#include "Physics/PathManager.h"

enum WallTypes {
    Top = 0,
    Bottom = 1,
    Left = 2,
    Right = 3,
    Center = 4,
    Ground = 5,
};

class Wall :
    public AGameObject, public CollisionListener
{
public:
    Wall(std::string name, WallTypes wallType);
    void initialize();
    void initialPos(sf::Vector2f pos);

    //Collision
    void onCollisionEnter(AGameObject* contact);
    void onCollisionExit(AGameObject* gameObject);

private:
    Collider* collider;
    WallTypes wallType = WallTypes::Top;

};

