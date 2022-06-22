#include "PlayerInputController.h"
#include "../Manager/ApplicationManager.h"

PlayerInputController::PlayerInputController(string name): GenericInputController(name)
{

}

PlayerInputController::~PlayerInputController() 
{
	GenericInputController::~GenericInputController();
}

void PlayerInputController::perform()
{
	bool keyflag = false;
	if (event.type == sf::Event::KeyPressed) {
		keyflag = true;
	}
	else if (event.type == sf::Event::KeyReleased) {
		keyflag = false;
	}

	switch (event.key.code) {
	case sf::Keyboard::W:
		this->moveUp = keyflag;
		break;
	case sf::Keyboard::S:
		this->moveDown = keyflag;
		break;
	case sf::Keyboard::A:
		this->moveLeft = keyflag;
		break;
	case sf::Keyboard::D:
		this->moveRight = keyflag;
		break;
	case sf::Keyboard::Space:
		this->fire = keyflag;
		break;
	}
}

bool PlayerInputController::isUp()
{
	return this->moveUp;
}

bool PlayerInputController::isDown()
{
	return this->moveDown;
}

bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}

bool PlayerInputController::hasFired()
{
	return this->fire;
}


