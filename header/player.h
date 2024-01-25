#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::RenderWindow& window);

    void update(float deltaTime);
    void draw();

    void handleInput(float deltaTime);

private:
    sf::RenderWindow& window;
    sf::CircleShape shape;
    float speed;
};

#endif
