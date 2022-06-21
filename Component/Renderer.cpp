#include "Renderer.h"

Renderer::Renderer(string name) : AComponent(name, AComponent::Renderer)
{
	this->type = AComponent::Renderer;
	this->renderStates = sf::RenderStates::Default;

}

Renderer::~Renderer()
{
	if(this->drawable = NULL)
		delete this->drawable;
	
	/*if (this->targetWindow != NULL)
		delete this->targetWindow;*/
	 
	AComponent::~AComponent();
}

void Renderer::assignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}

void Renderer::assignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}

void Renderer::setRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}

void Renderer::perform() {
	this->targetWindow->draw(*this->drawable, this->renderStates);
}