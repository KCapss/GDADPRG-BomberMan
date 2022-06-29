#pragma once
#include "AGameObject.h"
#include "Wall.h"

typedef  vector<vector<sf::Vector2f>> TileMap;

class WallManager: public AGameObject
{
public:
	WallManager(std::string name);
	void initialize();



private:

	void loadCenterWall();
	TileMap nonWalkableSpot;
	TileMap WalkableSpot;

	int rows = 0, columns = 0;
	int freeTile = 0;
	
	//All Walls
	Wall* boundariesTop;
	Wall* boundariesLeft;
	Wall* boundariesRight;
	Wall* boundariesBottom;

	//Wall* center;

	Wall* ground;

};

