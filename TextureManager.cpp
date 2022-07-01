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
	loadTexture("bomberMan", "Media/Assets/Player/SpriteSheet/PlayerSheets.png");
	loadTexture("defaultCrate", "Media/Assets/Objects/NonMovable/default_Crate.png");
	loadTexture("bombCrate", "Media/Assets/Objects/Bombs/bomb.png");
	loadTexture("bombVFX", "Media/Assets/Objects/Bombs/VFX/tile004.png");
	loadTexture("enem_1", "Media/Assets/Enemies/All_Enemies/IdleAnimation/Enem1_Left-1.png");


	//
	loadTexture("powerUp-1", "Media/Assets/Objects/PowerUp/AddBomb.png");
	loadTexture("Door", "Media/Assets/Objects/PowerUp/Door.png");
	

	//BG Divider
	loadTexture("wall", "Media/Assets/Objects/NonMovable/metalWall.png");
	sf::Texture* bgWall = getTexture("wall");
	bgWall->setRepeated(true);
	loadTexture("ground", "Media/Assets/Objects/NonMovable/default_ground_06.png");
	sf::Texture* bgGround = getTexture("ground");
	bgGround->setRepeated(true);

	//load UI
	loadTexture("ui_bg", "Media/Assets/UI/green_panel.png");
	loadTexture("ui_bar", "Media/Assets/UI/gray_flat.png");
	sf::Texture* ui_bar = getTexture("ui_bar");
	ui_bar->setRepeated(true);
	loadTexture("btn_normal", "Media/Assets/UI/offRed_button11.png");
	loadTexture("btn_pressed", "Media/Assets/UI/onRed_button13.png");

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



