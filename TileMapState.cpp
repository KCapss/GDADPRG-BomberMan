#include "TileMapState.h"
#include "PlayerState.h"


TileMapState* TileMapState::sharedInstance = NULL;

TileMapState* TileMapState::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new TileMapState();
	}

	return sharedInstance;
}

void TileMapState::loadAll()
{
	float x = (64.0f) + 32.0f;
	float y = (64.0f * 2.f) + 32.0f;

	float increment = 64.0f;

	for (int i = 0; i < 15; i++) {
		vector<sf::Vector2f> columnList;
		for (int j = 0; j < 11; j++) {

			sf::Vector2f tileSpot = sf::Vector2f((x)+(64.0f * i), (y)+(64.0f * j));
			if ((i == 0 && j == 0) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
				//Debugging
				string key = this->convertString(tileSpot);
				//cout << key << endl;
				this->mapLayout[key] = new TileState();
			}
			else {
				string key = this->convertString(tileSpot);
				//cout << key << endl;
				this->mapLayout[key] = new TileState();
			}
			
			columnList.push_back(tileSpot);
		}
		this->mapEnvinronment.push_back(columnList);
	}
	
}

void TileMapState::resetAll()
{
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {
			string key = this->convertString(this->mapEnvinronment[i][j]);

			this->mapLayout[key]->reset();
			this->mapLayout[key]->resetExplosion();

		}
	}
}

string TileMapState::convertString(sf::Vector2f Pos)
{
	int x = Pos.x;
	int y = Pos.y;

	string name = std::to_string(x) + " " + std::to_string(y);

	return name;
}

sf::Vector2f TileMapState::randomizeSpawn(string name)
{
	sf::Vector2f spawnPos(0, 0);

	if (spawnPriorities(name)) {
		return lookSpawnPriorities(name);
	}
	
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {

			int randNum = rand() % 200;

			if (randNum < 1) {


				if (this->checkOccupancy(this->mapEnvinronment[i][j])) {

					if ((i == 0 && j == 0) || (i == 1 && j == 0) || (i == 0 && j == 1))
					{
						//Empty
					}

					else if (((i == 0 && j == 2) || (i == 2 && j == 0)) && name == "enemy") {
						//Empty
					}

					else {
						cout << "Spawn Completeed" << endl;
						return this->mapEnvinronment[i][j];
					}
						
				}
				else {
					
				}
			}
		}
	}
	
	return randomizeSpawn(name);
}

bool TileMapState::spawnPriorities(string name)
{
	
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {
			string key = this->convertString(this->mapEnvinronment[i][j]);

			//For PowerUp
			if (mapLayout[key]->getName() == "PowerUp" &&
				(name != "PowerUp" || name != "EndLevel")) {
				return true;
			}

			if (mapLayout[key]->getName() == "EndLevel" &&
				(name != "PowerUp" || name != "EndLevel")) {
				return true;
			}
		}
	}

	return false;
}

sf::Vector2f TileMapState::lookSpawnPriorities(string name)
{
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {
			string key = this->convertString(this->mapEnvinronment[i][j]);

			//For PowerUp
			if (mapLayout[key]->getName() == "PowerUp") {
				return this->mapEnvinronment[i][j];
			}

			if (mapLayout[key]->getName() == "EndLevel") {
				return this->mapEnvinronment[i][j];
			}
		}
	}

	cout << "false" << endl;
	return sf::Vector2f(0, 0);
}

sf::Vector2f TileMapState::findNearestNeighbor(sf::Vector2f pos)
{
	float lowestDist = this->computeEuclideanDistance(pos, this->mapEnvinronment[0][0]);
	sf::Vector2f tempPos = this->mapEnvinronment[0][0];


	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {

			float currDistance = this->computeEuclideanDistance(pos, this->mapEnvinronment[i][j]);
			if (lowestDist > currDistance) {
				//cout << "distance: " << currDistance << endl;
				lowestDist = currDistance;
				tempPos = this->mapEnvinronment[i][j];


				//For Guarantee estimate
				if (lowestDist < 30.0f)
					return tempPos;
			}
			
		}
	}
	
	
	return tempPos;
}

void TileMapState::registerPosition(sf::Vector2f Pos, std::string name)
{
	string key = this->convertString(Pos);

	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not Registered" << std::endl;
	}

	else {
		
		//if(this->checkOccupancy(Pos))
		if(true){
			//std::cout << "Registerd Position" << std::endl;
			this->mapLayout[key]->initialize(Pos, name);

		}
		else {
			std::cout << "Not Available Position" << std::endl;
		}
		
	}

}

void TileMapState::unRegisterPosition(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not Registered" << std::endl;

	}

	else {
		this->mapLayout[key]->reset();
	}
}

float TileMapState::computeEuclideanDistance(sf::Vector2f A, sf::Vector2f B)
{
	//For X
	float Ax = A.x;
	float Bx = B.x;

	//For Y
	float Ay = A.y;
	float By = B.y;

	float difference = (abs(Ax - Bx) + abs(Ay - By));

	return difference;
}

bool TileMapState::checkOccupancy(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not missing" << std::endl;
		return false;
	}

	
	return this->mapLayout[key]->isOccupied();
}

void TileMapState::registerExplosion(sf::Vector2f Pos, int direction, int count)
{
	//Special Case
	if (direction == ObjectFacing::inCenter)
	{
		if (validTile(Pos) && !checkhasExploded(Pos)) {
			string key = this->convertString(Pos);
			this->mapLayout[key]->activateExplosion();
		}
	}

	//Cardinal Direction
	else {
		if (direction == ObjectFacing::lookUp)
		{
			Pos = sf::Vector2f(Pos.x, Pos.y - 64.0f);
		}

		else if (direction == ObjectFacing::lookDown)
		{
			Pos = sf::Vector2f(Pos.x, Pos.y + 64.0f);
		}

		else if (direction == ObjectFacing::lookLeft)
		{
			Pos = sf::Vector2f(Pos.x - 64.0f, Pos.y);
		}

		else if (direction == ObjectFacing::lookRight)
		{
			Pos = sf::Vector2f(Pos.x + 64.0f, Pos.y);
		}

		/*if (validTile(Pos) && !checkhasExploded(Pos))*/ //Return it later
		if (validTile(Pos)) {
			string key = this->convertString(Pos);
			this->mapLayout[key]->activateExplosion();

			/*cout << "Name : " << this->mapLayout[key]->getName() << endl;*/
			
			if (this->mapLayout[key]->getName() == "Box") {
				cout << this->mapLayout[key]->getName() << endl;
			}

			else if (this->mapLayout[key]->getName() == "projectile") {

			}

			else if (PlayerState::getInstance()->retrieveMaxRange() - 1 > count) {
				//cout << this->mapLayout[key]->getName() << endl;
				this->registerExplosion(Pos, direction, count + 1);
			}
		}

	}
	

}

void TileMapState::unregisterExplosion(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	this->mapLayout[key]->resetExplosion();
}

bool TileMapState::checkhasExploded(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not missing for explosion" << std::endl;
		return false;
	}

	return this->mapLayout[key]->hasinitiateExplosion();
}

bool TileMapState::validTile(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos dows not exist" << std::endl;
		return false;
	}
	/*std::cout << "This Pos is not missing for name: " << 
		this->mapLayout[key]->getName() << std::endl;*/

	if (this->mapLayout[key]->getName() == "Wall")
		return false;
	else
		return true;
}

sf::Vector2f TileMapState::onInitiateExplotion()
{
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {
			string key = this->convertString(this->mapEnvinronment[i][j]);

			if (this->mapLayout[key]->hasinitiateExplosion() &&
				!this->mapLayout[key]->hasExploded()) {
				this->mapLayout[key]->explosionSetActive();
				return this->mapEnvinronment[i][j];
			}
			
		}
	}

	cout << "Too many explotion " << endl;

}

int TileMapState::availableExplotion()
{
	int count = 0;
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {
			string key = this->convertString(this->mapEnvinronment[i][j]);

			if (this->mapLayout[key]->hasinitiateExplosion() &&
				!this->mapLayout[key]->hasExploded()) {
				count++;
			}

		}
	}

	return count;
}

void TileMapState::setActiveScene(string sceneName)
{
	this->activeScene = sceneName;
}

string TileMapState::retrieveActiveScene()
{
	return this->activeScene;
}


