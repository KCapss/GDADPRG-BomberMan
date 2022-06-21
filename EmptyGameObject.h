#pragma once
#include "AGameObject.h"
class EmptyGameObject: public AGameObject
{
public:
	EmptyGameObject(string name);
	~EmptyGameObject();
	void initialize();
};

