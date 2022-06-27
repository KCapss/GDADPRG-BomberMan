#pragma once
#include "AGameObject.h"
class Player :
    public AGameObject
{

public:
	Player(std::string name);
	void initialize();
	

private:
	const float SPEED_MULLTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
};

