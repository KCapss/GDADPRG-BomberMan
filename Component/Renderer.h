#pragma once
#include "AComponent.h"
#include <SFML/Graphics/RenderWindow.hpp>
class Renderer :
    public AComponent
{
public:
    Renderer(string name);
    ~Renderer();

    void assignTargetWindow(sf::RenderWindow* window);
    void assignDrawable(sf::Drawable* drawable);
    void setRenderStates(sf::RenderStates renderStates);

    void perform();
private:
    sf::RenderWindow* targetWindow =  NULL;
    sf::Drawable* drawable = NULL;
    sf::RenderStates renderStates;



};

