#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    sf::View view;
    bool cameraMoving;
    bool oPressed;

    void processEvents();
    void update(float deltaTime);
    void render();
};