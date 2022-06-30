#pragma once
#include "TileState.h"
#include "Player.h"
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
	void resetAll();

	void registerPosition(sf::Vector2f Pos, std::string name);
	void unRegisterPosition(sf::Vector2f Pos);

	//void registerExplosion
	string convertString(sf::Vector2f Pos);

	//Summon Randomizer
	sf::Vector2f randomizeSpawn(string name);
	bool spawnPriorities(string name);
	sf::Vector2f lookSpawnPriorities(string name);
	
	//
	sf::Vector2f findNearestNeighbor(sf::Vector2f pos);
	bool checkOccupancy(sf::Vector2f Pos);
	

	//Bomb Attributes
	void registerExplosion(sf::Vector2f Pos, int direction, int count);
	void unregisterExplosion(sf::Vector2f Pos);
	bool checkhasExploded(sf::Vector2f Pos);
	bool validTile(sf::Vector2f Pos);

	sf::Vector2f onInitiateExplotion();
	int availableExplotion();

private:
	//set constructor to private
	TileMapState() {};
	
	float computeEuclideanDistance(sf::Vector2f A, sf::Vector2f B);
	

	
	static TileMapState* sharedInstance;
	TileState* tileState;
	std::unordered_map <std::string, TileState*> mapLayout;
	TileMap mapEnvinronment;
	
};

