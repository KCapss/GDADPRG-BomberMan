#pragma once
#include "AComponent.h"
#include "../ObjectPooling/GameObjectPool.h"
#include "../Player.h"
#include "PlayerInputController.h"

class PlayerMovement: public AComponent
{
public:
	PlayerMovement(string name);
	~PlayerMovement();

	void perform();
	void adjustPos(Player* player);
	bool checkOutofBounds(Player* player, PlayerInputController* inputController);
	bool checkWalls(Player* player, PlayerInputController* inputController);
	

private:
	float SPEED_MULLTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 0.2f;
	float ticks = 0.0f;

	GameObjectPool* projectilePool;


};

