#include "EnemyBehaviour.h"
#include "../EnemyObject.h"
#include "../PlayerState.h"
#include "../Physics/PathManager.h"

EnemyBehaviour::EnemyBehaviour(string name) : AComponent(name, Script)
{
	this->reset();
}

void EnemyBehaviour::perform()
{
	EnemyObject* enemy = (EnemyObject*)this->getOwner();
	ObjectFacing enemOrientation = enemy->retrieveEnemOrientation();
	//Time Ticking
	ticks += deltaTime.asSeconds();

	//Randomizing Behaviours
		//Changing Pattern
	if (timer < ticks) {
		changePattern(Search);
		this->reset();
	}

	else {
		Collider* enemCollider = (Collider*)enemy->getComponentsofType(Physics)[0];
		if (PathManager::getInstance()->predictMovement(enemCollider,
			enemOrientation,
			NonCharacter))  
		{
			move();
		}

		else 
		{
			changePattern(Bounce);
		}

	}
		
	//Move
		//Checkinng for Collision
}

void EnemyBehaviour::reset()
{
	this->ticks = 0;
}

void EnemyBehaviour::changePattern(Tactics tactics)
{
	EnemyObject* enemy = (EnemyObject*)this->getOwner();
	ObjectFacing enemOrientation = enemy->retrieveEnemOrientation();
	//Decide which action to took

	int randomNum = 0;
	if (tactics == Tactics::Bounce) {
		randomNum = rand() % 4;

		//75% Prob of actual Bouncing
		if (randomNum > 0) {
			switch (enemOrientation) {
			case ObjectFacing::lookUp:
				enemy->changeOrientation(lookDown);
				break;

			case ObjectFacing::lookDown:
				enemy->changeOrientation(lookUp);
				break;

			case ObjectFacing::lookLeft:
				enemy->changeOrientation(lookRight);
				break;

			case ObjectFacing::lookRight:
				enemy->changeOrientation(lookLeft);
				break;
			}
		}

		//25% bounce in other direction
		else {
			switch (enemOrientation) {
			case ObjectFacing::lookUp:
				if(rand()% 2)
					enemy->changeOrientation((lookLeft));
				else
					enemy->changeOrientation((lookRight));

				break;

			case ObjectFacing::lookDown:
				if (rand() % 2)
					enemy->changeOrientation((lookLeft));
				else
					enemy->changeOrientation((lookRight));

				break;

			case ObjectFacing::lookLeft:
				if (rand() % 2)
					enemy->changeOrientation((lookUp));
				else
					enemy->changeOrientation((lookDown));

				break;

			case ObjectFacing::lookRight:
				if (rand() % 2)
					enemy->changeOrientation((lookUp));
				else
					enemy->changeOrientation((lookDown));

				break;
			}
		}

	}

	else if (tactics == Tactics::Search) {
		//Compute the difference
		sf::Vector2f enemPos = enemy->getTransformable()->getPosition();
		sf::Vector2f playerPos = PlayerState::getInstance()->retrievePlayerPos();

		ObjectFacing smartOrientX = ObjectFacing::inCenter;
		ObjectFacing smartOrientY = ObjectFacing::inCenter;

		float xDiff = playerPos.x - enemPos.x;
		float yDiff = playerPos.y - enemPos.y;

		/*cout << "Position List: Player - X: " <<  playerPos.x << " Y: " << playerPos.y << endl;
		cout << "Position List: Enemy - X: " << enemPos.x << " Y: " << enemPos.y << endl;*/

		if (xDiff < 0)
			smartOrientX = ObjectFacing::lookLeft;
		else if (xDiff >= 0)
			smartOrientX = ObjectFacing::lookRight;


		if (yDiff < 0)
			smartOrientY = ObjectFacing::lookUp;
		else if (yDiff >= 0)
			smartOrientY = ObjectFacing::lookDown;

		//Create Decision
		int smart = enemy->getIQ();
		randomNum = rand() % 10;

		if (randomNum < smart) {
			//Smart Play
			if (rand() % 2)
				enemy->changeOrientation(smartOrientX);
			else
				enemy->changeOrientation(smartOrientY);
		}

		else {
			switch (rand()%4) {
			case ObjectFacing::lookUp:
				enemy->changeOrientation(lookDown);
				break;

			case ObjectFacing::lookDown:
				enemy->changeOrientation(lookUp);
				break;

			case ObjectFacing::lookLeft:
				enemy->changeOrientation(lookRight);
				break;

			case ObjectFacing::lookRight:
				enemy->changeOrientation(lookLeft);
				break;
			}

		}
			
	}

}

void EnemyBehaviour::move()
{
	EnemyObject* enemy = (EnemyObject*)this->getOwner();
	ObjectFacing enemOrientation = enemy->retrieveEnemOrientation();

	float speed = enemy->retrieveSpeed();


	sf::Transformable* enemyTransformable = enemy->getTransformable();
	if (enemyTransformable == NULL) {
		cout << "enemyTransformable not found" << endl;
		return;
	}



	sf::Vector2f offset(0.0f, 0.0f);
	if (enemOrientation == ObjectFacing::lookUp) {
		offset.y -= speed;
		enemyTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (enemOrientation == ObjectFacing::lookDown) {
		offset.y += speed;
		enemyTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (enemOrientation == ObjectFacing::lookLeft) {
		offset.x -= speed;
		enemyTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (enemOrientation == ObjectFacing::lookRight) {
		offset.x += speed;
		enemyTransformable->move(offset * deltaTime.asSeconds());
	}

}
