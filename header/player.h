#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    float getSpeed() const;
    sf::View& getView();
    void update(float deltaTime);
    void draw();
    void handleInput(float deltaTime);

private:
    sf::RenderWindow& window;
    sf::Texture texture;
    sf::Sprite sprite;
    float speed = 200.f;
};

#endif
