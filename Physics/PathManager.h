#pragma once
#include "../Component/AComponent.h"
#include "../AGameObject.h"
#include "Collider.h"





typedef vector<Collider*> CollisionList;
//typedef vector<Collider*> Track

#include<vector>
#include<unordered_map>

enum CleaningTypes {
    Objects = 0,
    Walls = 1
};

enum ObjectTypes {
    Character = 2,
    NonCharacter = 3
};

class PathManager :
    public AComponent
{
public:
    static void initialize(string name, AGameObject* parent);
    static void destroy();
    static PathManager* getInstance();
    ~PathManager();

    //For GameObject
    void trackObject(Collider* object);
    void untrackObject(Collider* object);

    //For Wall
    void trackWallObject(Collider* object);
    void untrackWallObject(Collider* object);

    void perform() {};
    void operate();

    //For Player
    bool predictMovement(Collider *collider, int direction, int objType);
   
    bool collidedPath(sf::FloatRect A, sf::FloatRect B);

    //For Enemies

    //For Bomb
    void checkIntersection(Collider* collider, sf::FloatRect bounds);


    //Special Case

private:
    PathManager(string name) : AComponent(name, Script) {};
    PathManager(PathManager const&) : AComponent(name, Script) {};
    PathManager& operator=(PathManager const&) {};
    static PathManager* sharedInstance;

    CollisionList trackedObject;
    CollisionList wallTrackObject;

    CollisionList forCleaningObjects;
    CollisionList forCleaningWalls;

    void cleanUpObjects(CleaningTypes types);



};

