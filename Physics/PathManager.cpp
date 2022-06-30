#include "PathManager.h"
#include "../Player.h"
#include "../EnemyObject.h"
#include "../BombVFX.h"
#include <iostream>
#include <cmath>

//All Object


PathManager* PathManager::sharedInstance = NULL;
void PathManager::initialize(string name, AGameObject* parent)
{
    sharedInstance = new PathManager(name);
    parent->attachComponent(sharedInstance);
}

void PathManager::destroy()
{
    delete sharedInstance;
}

PathManager* PathManager::getInstance()
{
    return sharedInstance;
}

PathManager::~PathManager()
{

}

void PathManager::trackObject(Collider* object)
{
    object->setAlreadyCollided(false);
    this->trackedObject.push_back(object);

}

void PathManager::untrackObject(Collider* object)
{
    this->forCleaningObjects.push_back(object);
    this->cleanUpObjects(Objects);
}

void PathManager::trackWallObject(Collider* object)
{
    object->setAlreadyCollided(false);
    this->wallTrackObject.push_back(object);
}

void PathManager::untrackWallObject(Collider* object)
{
    this->forCleaningWalls.push_back(object);
    this->cleanUpObjects(Walls);
}

void PathManager::operate()
{
    for (int i = 0; i < this->wallTrackObject.size(); i++) {
        for (int j = 0; j < this->trackedObject.size(); j++) {

            if (this->wallTrackObject[i] != this->trackedObject[j] && //check if not same object
                this->wallTrackObject[i]->getOwner()->isEnabled() &&
                this->trackedObject[j]->getOwner()->isEnabled()) {

                //check collision between two objects
                if (this->wallTrackObject[i]->willCollide(this->trackedObject[j]) &&
                    !this->wallTrackObject[i]->alreadyCollided() &&
                    !this->trackedObject[j]->alreadyCollided()) {

                    //this->wallTrackObject[i]->collisionEnter(this->trackedObject[j]->getOwner());
                    this->trackedObject[j]->collisionEnter(this->wallTrackObject[i]->getOwner());

                    //this->trackedObject[i]->setAlreadyCollided(true);
                    //this->trackedObject[j]->setAlreadyCollided(true);
                }

                else if (!this->wallTrackObject[i]->willCollide(this->trackedObject[j])
                    && this->wallTrackObject[i]->alreadyCollided()
                    && this->trackedObject[j]->alreadyCollided()) {

                    this->wallTrackObject[i]->collisionExit(this->trackedObject[j]->getOwner());
                    this->trackedObject[j]->collisionExit(this->wallTrackObject[i]->getOwner());

                    this->wallTrackObject[i]->setAlreadyCollided(false);
                    this->trackedObject[j]->setAlreadyCollided(false);
                }

            }
        }
    }

    //std::cout << "---" << endl;
    for (int i = 0; i < this->trackedObject.size(); i++) {

        //std::cout << this->trackedObject[i]->getOwner()->isEnabled() << endl;
        this->trackedObject[i]->setChecked(false);
    }

    //this->cleanUpObjects();
}

bool PathManager::predictMovement(Collider* collider, int direction, int objType)
{
    //ObjPropeties
    Player* player;
    EnemyObject* enemy;
    float speed = 0;
    sf::FloatRect bounds = collider->getGlobalBounds();

    if (objType == ObjectTypes::Character) {
        player = (Player*)collider->getOwner();
        speed = player->retrieveSpeed() * deltaTime.asSeconds();
    }

    else {
        enemy = (EnemyObject*)collider->getOwner();
        speed = enemy->retrieveSpeed() * deltaTime.asSeconds();
        //cout << "No Character choice yet" << endl;
    }


   
    sf::Vector2f offset = sf::Vector2f(0, 0);
    if (direction == ObjectFacing::lookUp) {
        offset.y -= speed;

        bounds = sf::FloatRect(bounds.left ,
            bounds.top + offset.y,
            bounds.width,
            bounds.height);
    }

    else if (direction == ObjectFacing::lookDown) {
        offset.y += speed;

        bounds = sf::FloatRect(bounds.left,
            bounds.top + offset.y,
            bounds.width,
            bounds.height);
    }

    else if (direction == ObjectFacing::lookLeft) {
        offset.x -= speed;

        bounds = sf::FloatRect(bounds.left + offset.x,
            bounds.top,
            bounds.width,
            bounds.height);
    }

    else if (direction == ObjectFacing::lookRight) {
        offset.x += speed;

        bounds = sf::FloatRect(bounds.left + offset.x,
            bounds.top,
            bounds.width,
            bounds.height);
    }
    bounds = sf::FloatRect(bounds.left ,
        bounds.top,
        bounds.width - 8.0f,
        bounds.height - 8.0f);

    for (int i = 0; i < this->wallTrackObject.size(); i++) {
        sf::FloatRect wallBounds = wallTrackObject[i]->getGlobalBounds();

        wallBounds = sf::FloatRect(wallBounds.left,
            wallBounds.top ,
            wallBounds.width - 4.0f,
            wallBounds.height - 4.0f);


        //for bomb
        if (wallTrackObject[i]->getName() == "BombCollider") {
           
            
            bounds = sf::FloatRect(bounds.left,
                bounds.top,
                bounds.width + 3.0f ,
                bounds.height + 3.0f);


            if (bounds.intersects(wallBounds)) {
                if (wallTrackObject[i]->alreadyCollided() && collider->getName() == "Player") {
                    cout << "pass through" << endl;
                    return true;
                }
 
            }


            else if (!bounds.intersects(wallBounds) && wallTrackObject[i]->alreadyCollided())
            {
                if (collider->getName() == "Player") {
                    wallTrackObject[i]->setAlreadyCollided(false);
                }
                return true;
            }

            else if (!bounds.intersects(wallBounds) && !wallTrackObject[i]->alreadyCollided())
            {
                return true;
            }

            cout << "Px: " << bounds.left
                << " Py: " << bounds.top << endl;

            cout << "x: " << wallBounds.left
                << " y: " << wallBounds.top << endl;

            /*cout << "boundary error" << endl;
            cout << "Px: " << bounds.left
                << " Py: " << bounds.top << endl;

            cout << "x: " << wallBounds.left
                << " y: " << wallBounds.top << endl;*/
            return false;
        }

        
        if (bounds.intersects(wallBounds)) {
            return false;
        }
    }

    /*cout << "x: " << bounds.left
        << " y: " << bounds.top << endl;*/
    return true;
}



bool PathManager::collidedPath(sf::FloatRect A, sf::FloatRect B)
{
   //For X
    float aCenterX = A.left + (A.width)/2;
    float bCenterX = B.left + (B.width)/2;

    float aRadiusX = A.width / 2;
    float bRadiusX = B.width / 2;


   //For Y

    float aCenterY = A.top + (A.height) / 2;
    float bCenterY = B.top + (B.height) / 2;

    float aRadiusY = A.height / 2;
    float bRadiusY = B.height / 2;

    //Compute X
    if (abs(aCenterX - bCenterX) < (aRadiusX + bRadiusX)) {
        if (abs(aCenterY - bCenterY) < (aRadiusY + bRadiusY))
            return true;
    }
    
    
    return false;
}

void PathManager::checkIntersection(Collider* collider, sf::FloatRect bounds)
{

    BombVFX* bombVFX = (BombVFX*)collider->getOwner();


    for (int i = 0; i < this->wallTrackObject.size(); i++) {
        sf::FloatRect wallBounds = wallTrackObject[i]->getGlobalBounds();

       /* wallBounds = sf::FloatRect(wallBounds.left,
            wallBounds.top + 32.0f,
            wallBounds.width - 32.0f,
            wallBounds.height  - 32.0f);*/

        wallBounds = sf::FloatRect(wallBounds.left,
            wallBounds.top + 32.0f,
            wallBounds.width,
            wallBounds.height);

       // cout << "Name: " << wallTrackObject[i]->getName() << endl;
        if (wallTrackObject[i]->getName() == "Box") {

            if (bounds.intersects(wallBounds)) {
                wallTrackObject[i]->collisionExit(collider->getOwner());
                //break;
            }
            
        }
    }
}

void PathManager::cleanUpObjects(CleaningTypes types)
{

    if (types == CleaningTypes::Objects) {
        for (int i = 0; i < this->forCleaningObjects.size(); i++) {
            this->trackedObject.erase(this->trackedObject.begin() + i);
        }

        this->forCleaningObjects.clear();
    }

    else if (types == CleaningTypes::Walls) {
        CollisionList::iterator itr = wallTrackObject.begin();

        int index;
        for (int i = 0; i < this->forCleaningWalls.size(); i++) {
            int j = 0;
            while (itr != wallTrackObject.end()) {
                
                if (wallTrackObject[j] == forCleaningWalls[i]) {
                   /* cout << "Found " << j << endl;*/
                    index = j;
                    break;
                    
                }

                itr++;
                j++;
            }

            this->wallTrackObject.erase(this->wallTrackObject.begin() + index);
            this->wallTrackObject.shrink_to_fit();
        
        }

        this->forCleaningWalls.clear();
    }
    
}
