#pragma warning(suppress : 4996)
#include "PlayerAnimation.h"

#include "PlayerInputController.h"
#include "../GameObjectManager.h"

PlayerAnimation::PlayerAnimation(string name): AComponent(name, Script)
{
}

void PlayerAnimation::loadAll()
{
	
	
    //1. Parse a JSON file
    FILE* file = fopen("Media/Assets/Player/SpriteSheet/PlayerSheets.json", "rb");

    //2. Check if we opened successully 
    assert(file != 0);


    char readBuffer[65536]; //specific file size;
    rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));


    //Parse data here
    doc.ParseStream(is);
    fclose(file);

    //4. Read Data And store it as array
    rapidjson::Value& framesource = doc["frames"]; //Contain all Name of the Sprite
    this->maxSize = framesource.MemberCount(); //determine the count

    for (rapidjson::Value::ConstMemberIterator itr = doc["frames"].MemberBegin();
        itr != doc["frames"].MemberEnd(); itr++) {

        SpriteNameList.push_back(itr->name.GetString());

    }

}

void PlayerAnimation::perform()
{
    Player* player = (Player*)this->getOwner();
    PlayerInputController* inputController = (PlayerInputController*)(player->getComponentsofType(ComponentType::Input)[0]);

    ticks += deltaTime.asSeconds();

    if (ticks > this->timer) {
        ticks = 0;
        if (inputController->isUp()) {
            if (prevFacing != player->retrieveOrientation()) {
                iterate = 0;
                prevFacing = player->retrieveOrientation();
            }

            nextSprite(9 + iterate);
            iterate++;




        }
        else if (inputController->isDown()) {

            if (prevFacing != player->retrieveOrientation()) {
                iterate = 0;
                prevFacing = player->retrieveOrientation();
            }

            nextSprite(0 + iterate);
            iterate++;




        }
        else if (inputController->isLeft()) {
            if (prevFacing != player->retrieveOrientation()) {
                iterate = 0;
                prevFacing = player->retrieveOrientation();
            }

            nextSprite(3 + iterate);
            iterate++;




        }
        else if (inputController->isRight()) {
            if (prevFacing != player->retrieveOrientation()) {
                iterate = 0;
                prevFacing = player->retrieveOrientation();
            }

            nextSprite(6 + iterate);
            iterate++;



        }


        if (iterate > 2) {
            iterate = 0;
        }

    
    }

}

void PlayerAnimation::nextSprite(int offset)
{
    rapidjson::Value& framesource = doc["frames"]; //Contain all Name of the Sprite
    rapidjson::Value& source = framesource[(framesource.MemberBegin() + offset)->name.GetString()];
    rapidjson::Value& dimension = source[(source.MemberBegin())->name.GetString()];

    //Debug Testing Purpose
    //std::cout << (framesource.MemberBegin() + offset)->name.GetString() << std::endl;

    int x, y, w, h;

    x = (dimension.MemberBegin())->value.GetInt();
    y = (dimension.MemberBegin() + 1)->value.GetInt();
    w = (dimension.MemberBegin() + 2)->value.GetInt();
    h = (dimension.MemberBegin() + 3)->value.GetInt();

   /* std::cout << "x: " << x
        << "y: " << y
        << "w: " << w
        << "h: " << h << std::endl;*/

    Player* player = (Player*)this->getOwner();
    player->setTextureRect(x, y, w, h);
}
