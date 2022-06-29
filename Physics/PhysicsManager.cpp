#include "PhysicsManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = NULL;
void PhysicsManager::initialize(string name, AGameObject* parent)
{
    sharedInstance = new PhysicsManager(name);
    parent->attachComponent(sharedInstance);
}

void PhysicsManager::destroy()
{
    delete sharedInstance;
}

PhysicsManager* PhysicsManager::getInstance()
{
    return sharedInstance;
}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::trackObject(Collider* object)
{
    object->setAlreadyCollided(false);
    this->trackedObject.push_back(object);

}

void PhysicsManager::untrackObject(Collider* object)
{
    this->forCleaningObjects.push_back(object);
}

void PhysicsManager::perform()
{
    for (int i = 0; i < this->trackedObject.size(); i++) {
        for (int j = 0; j < this->trackedObject.size(); j++) {
            
            if (this->trackedObject[i] != this->trackedObject[j] && //check if not same object
                this->trackedObject[i]->getOwner()->isEnabled() &&
                this->trackedObject[j]->getOwner()->isEnabled()) {

                //check collision between two objects
                if (this->trackedObject[i]->willCollide(this->trackedObject[j]) &&
                    !this->trackedObject[i]->alreadyCollided() &&
                    !this->trackedObject[j]->alreadyCollided()) {

                    this->trackedObject[i]->collisionEnter(this->trackedObject[j]->getOwner());
                    this->trackedObject[j]->collisionEnter(this->trackedObject[i]->getOwner());

                    //this->trackedObject[i]->setAlreadyCollided(true);
                    //this->trackedObject[j]->setAlreadyCollided(true);
                }

                else if (!this->trackedObject[i]->willCollide(this->trackedObject[j])
                    && this->trackedObject[i]->alreadyCollided()
                    && this->trackedObject[j]->alreadyCollided()) {

                    this->trackedObject[i]->collisionExit(this->trackedObject[j]->getOwner());
                    this->trackedObject[j]->collisionExit(this->trackedObject[i]->getOwner());

                    this->trackedObject[i]->setAlreadyCollided(false);
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

void PhysicsManager::cleanUpObjects()
{
    /*for (int i = 0; i < this->forCleaningObjects.size(); i++) {
        this->trackedObject.erase(this->trackedObject.begin() + i);
    }

    this->forCleaningObjects.clear();*/

    CollisionList::iterator itr = trackedObject.begin();

    int index;
    for (int i = 0; i < this->forCleaningObjects.size(); i++){
        itr = trackedObject.begin();

        int j = 0;
        while (itr != trackedObject.end()) {

            if (trackedObject[j] == forCleaningObjects[i]) {
               /* cout << "Found " << j << endl;*/
                index = j;
                break;

            }

            itr++;
            j++;
        }

        this->trackedObject.erase(this->trackedObject.begin() + index);
        this->trackedObject.shrink_to_fit();

    }

    if(forCleaningObjects.size() > 0)
        this->forCleaningObjects.clear();
}
