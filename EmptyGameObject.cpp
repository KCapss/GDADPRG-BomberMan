#include "EmptyGameObject.h"

EmptyGameObject::EmptyGameObject(string name) : AGameObject(name)
{
}

EmptyGameObject::~EmptyGameObject()
{
	AGameObject::~AGameObject();
}

void EmptyGameObject::initialize()
{

}
