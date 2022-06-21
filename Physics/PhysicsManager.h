#pragma once
#include "../Component/AComponent.h"
#include "../AGameObject.h"
#include "Collider.h"

#include<vector>
#include<unordered_map>

typedef vector<Collider*> CollisionList;
class PhysicsManager :
    public AComponent
{
public:
    static void initialize(string name, AGameObject* parent);
    static void destroy();
    static PhysicsManager* getInstance();
    ~PhysicsManager();

    void trackObject(Collider* object);
    void untrackObject(Collider* object);
    void perform();

private:
    PhysicsManager(string name) : AComponent(name, Script) {};
    PhysicsManager(PhysicsManager const&) : AComponent(name, Script) {};
    PhysicsManager& operator=(PhysicsManager const&) {};
    static PhysicsManager* sharedInstance;

    CollisionList trackedObject;
    CollisionList forCleaningObjects;

    void cleanUpObjects();


};

