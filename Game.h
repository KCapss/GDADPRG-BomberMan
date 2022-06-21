#pragma once

#include "GameObjectManager.h"

#include <SFML/Graphics.hpp>






class Game
{
public:
	static const int GAME_WINDOW_WIDTH = 1024;
	static const int GAME_WINDOW_HEIGHT = 768;

	Game();
	void run();
	const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
	


private:
	void processEvent();
	void update(sf::Time);
	void render();
	
	//Extra
	void genPath();

	
private:
	sf::RenderWindow mWindow;
	//sf::Time deltaTime;
	std::vector<std::string> path;
	
	
private:
	

};

