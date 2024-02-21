#include "mouse.h"

MouseData::MouseData() {}

sf::Vector2i MouseData::getScreenPos() { return mousePosScreen; }
sf::Vector2i MouseData::getWindowPos() { return mousePosWindow; }
sf::Vector2f MouseData::getViewPos() { return mousePosView; }
sf::Vector2i MouseData::getGridPos() { return mousePosGrid; }

void MouseData::update(float deltaTime, Camera camera, sf::RenderWindow &window, unsigned gridSizeU)
{
    handleMouseMovement(deltaTime, camera, window, gridSizeU);
}
void MouseData::handleMouseMovement(float deltaTime, Camera camera, sf::RenderWindow &window, unsigned gridSizeU)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);
    window.setView(camera.getView());
    mousePosView = window.mapPixelToCoords(mousePosWindow);
    if (mousePosView.x >= 0.f)
    {
        mousePosGrid.x = mousePosView.x / gridSizeU;
    }
    if (mousePosView.y >= 0.f)
    {
        mousePosGrid.y = mousePosView.y / gridSizeU;
    }
    window.setView(window.getDefaultView());
}
