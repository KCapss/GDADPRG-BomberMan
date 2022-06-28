#include "BombBehaviour.h"

BombBehaviour::BombBehaviour(string name): AComponent(name, Script)
{
}

void BombBehaviour::perform()
{
	this->ticks += this->deltaTime.asSeconds();

	if (this->ticks > 3.0f) {
		reset();
		//Do some action


		//RemoveObject

	}
}

void BombBehaviour::reset()
{
	this->ticks = 0.0f;
}
