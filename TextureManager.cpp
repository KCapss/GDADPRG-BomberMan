#include <stddef.h>
#include <iostream>
#include "TextureManager.h"


TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
	//initial only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new TextureManager();
	}

	return sharedInstance;

}
void TextureManager::loadAll()
{
	
	//load obj
	loadTexture("eagle", "Media/Eagle.png");
	loadTexture("raptor", "Media/Raptor.png");
	loadTexture("avenger", "Media/Avenger.png");
	loadTexture("bullet", "Media/Bullet.png");

	//BG Divider
	loadTexture("desert_bg", "Media/Texture/Desert.png");
	sf::Texture* bgTex;
	bgTex = getTexture("desert_bg");
	bgTex->setRepeated(true);

	//load UI
	loadTexture("ui_bg", "Media/f.png");
	loadTexture("ui_bar", "Media/bar_1.png");
	loadTexture("btn_normal", "Media/b_4.png");
	loadTexture("btn_pressed", "Media/b_5.png");

	//TitleScreen
	loadTexture("title_bg", "Media/TitleScreenBG.png");

}

sf::Texture* TextureManager::getTexture(std::string key)
{
	if (textureMap[key] != NULL) {
		return textureMap[key];
	}

	else {
		std::cout << "No texture found for " << key << std::endl;
		return NULL;
	}

}

void TextureManager::loadTexture(std::string key, std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}


void TextureManager::testFunction() {
	std::cout << " Hello Single T" << std::endl;	

}



