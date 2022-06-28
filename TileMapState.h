#pragma once
#include "TileState.h"
#include <iostream>

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

typedef  vector<vector<sf::Vector2f>> TileMap;
//typedef TileState data;

class TileMapState: sf::NonCopyable
{

public:
	static TileMapState* getInstance();
	void loadAll();

	void registerPosition(sf::Vector2f Pos, std::string name);
	string convertString(sf::Vector2f Pos);

	//Summon Randomizer
	sf::Vector2f randomizeSpawn(string name);
	


private:
	//set constructor to private
	TileMapState() {};
	
	
	bool checkOccupancy(sf::Vector2f Pos);
	
	static TileMapState* sharedInstance;
	TileState* tileState;
	std::unordered_map <std::string, TileState*> mapLayout;
	TileMap mapEnvinronment;
	
};
