#include "WallManager.h"
#include "GameObjectManager.h"

#include <iostream>
using namespace std;

WallManager::WallManager(std::string name): AGameObject (name)
{
	this->loadCenterWall();

}

void WallManager::initialize()
{
	this->ground = new Wall("Wall", Ground);


	this->boundariesTop= new Wall("Wall", Top);
	this->boundariesLeft = new Wall("Wall", Left);
	this->boundariesRight = new Wall("Wall", Right);
	this->boundariesBottom = new Wall("Wall", Bottom);

	//Instantiate the center wall

	this->attachChild(ground);
	
	int x = 0, y = 0;
	for (int i = 0; i < ((rows) * (columns)); i++) {
		
		Wall* pillar = new Wall("Wall", Center);
		pillar->initialPos(nonWalkableSpot[x][y]);
		this->attachChild(pillar);
		y++;

		if (y == rows) {
			y = 0;
			x += 1;
			
		}
		//nonWalkableSpot[x][y]
		
	}
	
	this->attachChild(boundariesTop);
	this->attachChild(boundariesLeft);
	this->attachChild(boundariesRight);
	this->attachChild(boundariesBottom);

}

void WallManager::loadCenterWall()
{
	float x = (64.0f) + 32.0f;
	float y = (64.0f * 2.f) + 32.0f;

	float increment = 64.0f;

	for (int i = 0; i < 15; i++) {

		vector<sf::Vector2f> columnList;
		vector<sf::Vector2f> walkableColumn;
		for (int j = 0; j < 11; j++) {
			
			if ((i % 2) == 1) {
				if ((j % 2) == 1) {
					cout << "column: " << i <<
						" row: " << j << endl;
					sf::Vector2f wallPos = sf::Vector2f((x)+(64.0f * i), (y)+(64.0f * j));
					columnList.push_back(wallPos);
				}

				else {
					sf::Vector2f wallPos = sf::Vector2f((x)+(64.0f * i), (y)+(64.0f * j));
					walkableColumn.push_back(wallPos);
					freeTile++;
				}

			}	
			else {
				sf::Vector2f wallPos = sf::Vector2f((x)+(64.0f * i), (y)+(64.0f * j));
				walkableColumn.push_back(wallPos);
				freeTile++;
			}
		}
		if (columnList.size() != 0) {
			
			this->nonWalkableSpot.push_back(columnList);
			
		}
		this->WalkableSpot.push_back(walkableColumn);
	}
	this->rows = this->nonWalkableSpot[0].size();
	this->columns = this->nonWalkableSpot.size();


}
