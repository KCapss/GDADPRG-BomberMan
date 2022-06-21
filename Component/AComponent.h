#pragma once
#include <SFML/System.hpp>
#include <string>

using namespace std;

class AGameObject;

class AComponent
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	AComponent(string name, ComponentType type);
	virtual ~AComponent();

	void attachOwner(AGameObject* owner);
	void detachOwner();

	AGameObject* getOwner();
	ComponentType getType();
	string getName();

	void setDeltaTime(sf::Time deltaTime);
	virtual void perform() = 0;

	

protected:
	AGameObject* owner;
	ComponentType type;
	string name;
	sf::Time  deltaTime; // return to private if not working

	




};

