#pragma once
#include  <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include"Component/AComponent.h"


class AGameObject
{
public:
	AGameObject(std::string name);
	virtual ~AGameObject();
	virtual void initialize() = 0;
	virtual void processInput(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
	std::string getName();

	//New - SceneGraph
	void attachChild(AGameObject* child);
	void detachChild(AGameObject* child);
	void setPosition(float x, float y);

	//New - ComponentSystem
	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentbyName(string name);
	AComponent* findComponentbyType(AComponent::ComponentType type, string name);
	std::vector <AComponent*> getComponentsofType(AComponent::ComponentType type);
	std::vector <AComponent*> getComponentsofTypeRecursive(AComponent::ComponentType type);

	//New-ObjectPool
	void setEnabled(bool flag);
	bool isEnabled();

	//New-Physics
	sf::Transform getGlobalTransform();


	sf::Transformable* getTransformable();
	AGameObject* getParent();

protected:
	void setParent(AGameObject* gameObject);

	sf::Transformable transformable;
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<AGameObject*> childList;
	std::vector<AComponent*> componentList;

	

private:
	AGameObject* mParent;
	bool enabled = true;
	/*std::vector<AComponent*> getComponentRecursiveProper(AGameObject* object,
		AComponent::ComponentType type,
		std::vector<AComponent*> foundList);*/

};

