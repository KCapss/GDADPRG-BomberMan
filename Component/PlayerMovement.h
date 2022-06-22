#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"

class PlayerMovement: public AComponent
{
public:
	PlayerMovement(string name);
	~PlayerMovement();

	void perform();

private:
	const float SPEED_MULLTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 0.2f;
	float ticks = 0.0f;

	GameObjectPool* projectilePool;


};

