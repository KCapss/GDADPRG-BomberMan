#pragma once
#include "AComponent.h"

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/stringbuffer.h>


#include "../Player.h";

#include <iostream>
#include <string>
#include <vector>

class PlayerAnimation :
    public AComponent
{

public:
    typedef std::vector<int> spriteSrcSize;

    PlayerAnimation(string name);
    void loadAll();
    void perform();
   
    void nextSprite(int offset);
    //Process Input


private:
    const float timer = 0.1f;
    float ticks = 0.0f;

    int iterate = 0;
    int maxSize;
    ObjectFacing prevFacing = ObjectFacing::lookDown;

    rapidjson::Document doc;
    std::vector <std::string> SpriteNameList;
    std::vector <spriteSrcSize> spriteSrcList;
};

