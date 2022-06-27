#pragma once
#include "AGameObject.h"
#include "Physics/PathManager.h"
#include "Physics/PhysicsManager.h"

enum PlayerFacing {
	playerUp = 0,
	playerDown = 1,
	playerLeft = 2,
	playerRight = 3
};

class Player :
    public AGameObject, public CollisionListener
{

public:
	Player(std::string name);
	void initialize();

	//Setter
	void changeOrientation(PlayerFacing playerOrientation);
	void changeBlockStatus(bool flag);

	//Getter
	PlayerFacing retrieveOrientation();
	bool getBlockedStatus();
	float retrieveSpeed();

	//Collision
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* gameObject);

protected:
	bool isBlocked = false;


private:
	const float SPEED_MULLTIPLIER = 300.0f;

	PlayerFacing playerOrientation = PlayerFacing::playerDown;
	bool canMove = true;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	Collider* collider;


};

