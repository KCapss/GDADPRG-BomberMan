#pragma once
#include "GenericInputController.h"
class PlayerInputController :
    public GenericInputController
{
public:
    PlayerInputController(string name);
    ~PlayerInputController();

	void perform();
	bool isUp();
	bool isDown();
	bool isLeft();
	bool isRight();
	bool hasFired();



private:
	const float SPEED_MULLTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool fire = false;

};

