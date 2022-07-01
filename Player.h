#pragma once
#include "AGameObject.h"
#include "Physics/PathManager.h"
#include "Physics/PhysicsManager.h"

enum ObjectFacing {
	lookUp = 0,
	lookDown = 1,
	lookLeft = 2,
	lookRight = 3,
	inCenter = 4
};

class Player :
    public AGameObject, public CollisionListener
{

public:
	Player(std::string name);
	void initialize();

	//Setter
	void changeOrientation(ObjectFacing playerOrientation);
	void changeBlockStatus(bool flag);
	void incrementSpeed(float speed);

	//Getter
	ObjectFacing retrieveOrientation();
	bool getBlockedStatus();
	float retrieveSpeed();

	//Collision
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);

	void incrementBombUsedCount(int count);
	int getUsedBombCount();

protected:
	bool isBlocked = false;


private:
	float SPEED_MULLTIPLIER = 300.0f;

	int usedBombCount;
	

	ObjectFacing playerOrientation = ObjectFacing::lookDown;
	bool canMove = true;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	Collider* collider;


};

