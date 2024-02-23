#ifndef MOUSE_H
#define MOUSE_H
#include <SFML/Graphics.hpp>

class MouseData {
public:
    MouseData();
    sf::Vector2i getScreenPos();
    sf::Vector2i getWindowPos();
    sf::Vector2f getViewPos();
    sf::Vector2i getGridPos();
    void update(float deltaTime, Camera camera, sf::RenderWindow& window, unsigned gridSizeU);
    void handleMouseMovement(float deltaTime, Camera camera, sf::RenderWindow& window, unsigned gridSizeU);    

private:
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;
};

#endif