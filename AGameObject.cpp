#include "AGameObject.h"
#include "Component/GenericInputController.h"
#include "Component/Renderer.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{

	for (int i = 0; i < componentList.size(); i++) {
		delete componentList[i];
	}
	componentList.clear();
	componentList.shrink_to_fit();

	for (int i = 0; i < childList.size(); i++) {
		delete childList[i];
	}
	childList.clear();
	childList.shrink_to_fit();

	if (this->mParent != NULL) {
		this->mParent = NULL; //do not delete parent
	}
}

void AGameObject::processInput(sf::Event event)
{

	if (!this->isEnabled()) {
		return;
	}

	std::vector<AComponent*> componentList = this->getComponentsofType(AComponent::ComponentType::Input);
	for (int j = 0; j < componentList.size(); j++) {
		((GenericInputController*)componentList[j])->assignEvent(event);
		componentList[j]->perform();
	}

	//process input here
	for (int i = 0; i < this->childList.size(); i++) {
		childList[i]->processInput(event);
	}

}

void AGameObject::update(sf::Time deltaTime)
{

	if (!this->isEnabled()) {
		return;
	}

	std::vector<AComponent*> componentList = this->getComponentsofType(AComponent::ComponentType::Script);
	for (int j = 0; j < componentList.size(); j++) {
		componentList[j]->setDeltaTime(deltaTime);
		componentList[j]->perform();

	}


	for (int i = 0; i < childList.size(); i++) {
		childList[i]->update(deltaTime);
	}

}

void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{

	if (!this->isEnabled()) {
		return;
	}

	std::vector<AComponent*> componentList = this->getComponentsofType(AComponent::ComponentType::Renderer);

	renderStates.transform = renderStates.transform * this->transformable.getTransform();

	/*targetWindow->draw(*sprite, renderStates);*/
	
	for (int j = 0; j < componentList.size(); j++) {
		Renderer* renderer = (Renderer*)componentList[j];
		renderer->assignTargetWindow(targetWindow);
		renderer->setRenderStates(renderStates);
		renderer->perform();
	}

	for (int i = 0; i < this->childList.size(); i++) {
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}

}

std::string AGameObject::getName()
{
	return name;
}

void AGameObject::attachChild(AGameObject* child)
{
	this->childList.push_back(child);
	child->setParent(this);
	child->initialize();
}

void AGameObject::detachChild(AGameObject* child)
{
	int index = -1;
	for (int i = 0; i < this->childList.size(); i++) {
		if (this->childList[i] == child) {
			index = i;
		}
	}

	if (index != -1) {
		this->childList.erase(this->childList.begin() + index);
	}

}

void AGameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}

void AGameObject::setTextureRect(int left, int top, int width, int height)
{
	this->sprite->setTextureRect(sf::IntRect(left, top, width, height));
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);

}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			this->componentList[i]->detachOwner();
			break;
		}
	}

	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentbyName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentbyType(AComponent::ComponentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}
	return NULL;
}

std::vector<AComponent*> AGameObject::getComponentsofType(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}
	return foundList;
}

std::vector<AComponent*> AGameObject::getComponentsofTypeRecursive(AComponent::ComponentType type)
{
	return std::vector<AComponent*>();
}

void AGameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

sf::Transform AGameObject::getGlobalTransform()
{
	AGameObject* parentObj = this;
	vector<AGameObject*> parentList;

	while (parentObj != NULL) {
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();

	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--) {
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}

	return transform;

	
}

sf::Transformable* AGameObject::getTransformable()
{
	return &this->transformable;

}

AGameObject* AGameObject::getParent()
{
	return this->mParent;
}

void AGameObject::setParent(AGameObject* parent)
{
	this->mParent = parent;
}

//Enable Later
//std::vector<AComponent*> AGameObject::getComponentsofTypeRecursive(AComponent::ComponentType type)
//{
//	std::vector<AComponent*> foundList;
//	for (int i = 0; i < this->componentList.size(); i++) {
//		if (this->componentList[i]->getType() == type) {
//			foundList.push_back(this->componentList[i]);
//		}
//	}
//
//	for (int i = 0; i < this->childList.size(); i++) {
//		foundList = this->getComponentRecursiveProper(this->childList[i], type, foundList);
//	}
//	return foundList;
//}




