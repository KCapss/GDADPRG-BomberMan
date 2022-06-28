#include "TileMapState.h"


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
	
	for (int i = 0; i < this->mapEnvinronment.size(); i++) {
		for (int j = 0; j < this->mapEnvinronment[i].size(); j++) {

			int randNum = rand() % 200;
			if (randNum < 1) {
				if (this->checkOccupancy(this->mapEnvinronment[i][j])) {
					return this->mapEnvinronment[i][j];
				}
				else {
					/*cout << "occupied X: " <<
						this->mapEnvinronment[i][j].x <<
						" Y: " << this->mapEnvinronment[i][j].y << endl;*/
				}
			}
		}
	}
	
	return randomizeSpawn(name);
}

void TileMapState::registerPosition(sf::Vector2f Pos, std::string name)
{
	string key = this->convertString(Pos);

	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not Registered" << std::endl;
	}

	else {
		
		if(this->checkOccupancy(Pos)){
			//std::cout << "Registerd Position" << std::endl;
			this->mapLayout[key]->initialize(Pos, name);

		}
		else {
			std::cout << "Not Available Position" << std::endl;
		}
		
	}

}

bool TileMapState::checkOccupancy(sf::Vector2f Pos)
{
	string key = this->convertString(Pos);
	if (this->mapLayout[key] == NULL) {
		std::cout << "This Pos is not Registered" << std::endl;
		return false;
	}

	
	return this->mapLayout[key]->isOccupied();
}


