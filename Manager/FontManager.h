#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class FontManager :
	sf::NonCopyable
{
public:
	static FontManager* getInstance();

	void loadAll();
	sf::Font* getFont(std::string);

	
private:
	//set constructor to private
	FontManager() {};
	static FontManager* sharedInstance;

	void loadFont(std::string, std::string);
	std::unordered_map<std::string, sf::Font*> fontMap;
};

