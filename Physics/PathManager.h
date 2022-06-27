#pragma once
#include "../Component/AComponent.h"
#include "../AGameObject.h"
#include "Collider.h"

#include "../Player.h"



typedef vector<Collider*> CollisionList;
//typedef vector<Collider*> Track

#include<vector>
#include<unordered_map>


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

    bool predictMovement(Collider *collider, int direction);
    bool collidedPath(sf::FloatRect A, sf::FloatRect B);


    //Special Case

private:
    PathManager(string name) : AComponent(name, Script) {};
    PathManager(PathManager const&) : AComponent(name, Script) {};
    PathManager& operator=(PathManager const&) {};
    static PathManager* sharedInstance;

    CollisionList trackedObject;
    CollisionList wallTrackObject;

    CollisionList forCleaningObjects;

    void cleanUpObjects();



};

