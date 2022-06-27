#include "PathManager.h"
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
}

void PathManager::trackWallObject(Collider* object)
{
    object->setAlreadyCollided(false);
    this->wallTrackObject.push_back(object);
}

void PathManager::untrackWallObject(Collider* object)
{
    this->forCleaningObjects.push_back(object);
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

    this->cleanUpObjects();
}

bool PathManager::predictMovement(Collider* collider, int direction)
{
    //ObjPropeties
    Player* player = (Player*)collider->getOwner();
   
    

    //Sprite ProperTies
    sf::FloatRect bounds = collider->getGlobalBounds();
    //sf::Vector2u textureSize = s
    //player->getTransformable()

   
    sf::Vector2f offset = sf::Vector2f(0, 0);
    if (direction == PlayerFacing::playerUp) {
        offset.y -= player->retrieveSpeed() * deltaTime.asSeconds();

        bounds = sf::FloatRect(bounds.left ,
            bounds.top + offset.y,
            bounds.width,
            bounds.height);
    }

    else if (direction == PlayerFacing::playerDown) {
        offset.y += player->retrieveSpeed() * deltaTime.asSeconds();

        bounds = sf::FloatRect(bounds.left,
            bounds.top + offset.y,
            bounds.width,
            bounds.height);
    }

    else if (direction == PlayerFacing::playerLeft) {
        offset.x -= player->retrieveSpeed() * deltaTime.asSeconds();

        bounds = sf::FloatRect(bounds.left + offset.x,
            bounds.top,
            bounds.width,
            bounds.height);
    }

    else if (direction == PlayerFacing::playerRight) {
        offset.x += player->retrieveSpeed() * deltaTime.asSeconds();

        bounds = sf::FloatRect(bounds.left + offset.x,
            bounds.top,
            bounds.width,
            bounds.height);
    }
    bounds = sf::FloatRect(bounds.left + 8.0f,
        bounds.top + 8.0f,
        bounds.width - 8.0f,
        bounds.height - 8.0f);

    for (int i = 0; i < this->wallTrackObject.size(); i++) {
        sf::FloatRect wallBounds = wallTrackObject[i]->getGlobalBounds();

        wallBounds = sf::FloatRect(wallBounds.left + 8.0f,
            wallBounds.top + 8.0f,
            wallBounds.width - 8.0f,
            wallBounds.height - 8.0f);
        /*cout << "x: " << wallBounds.left
            << " y: " << wallBounds.top << endl;*/
        if (bounds.intersects(wallBounds)) {
            /*cout << "collide" << endl;
            cout << "x: " << wallBounds.left
                << " y: " << wallBounds.top << endl;*/
         
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

void PathManager::cleanUpObjects()
{
    for (int i = 0; i < this->forCleaningObjects.size(); i++) {
        this->trackedObject.erase(this->trackedObject.begin() + i);
    }

    this->forCleaningObjects.clear();
}
