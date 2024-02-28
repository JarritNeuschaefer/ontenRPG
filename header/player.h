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
    void animate(float deltaTime);
    void draw();
    void handleInput(float deltaTime);
    void changeTexture(int row, int coluomn);
    enum Direction {Up,Down,Left,Right};
    void setDirection(Direction newDirection);
    Direction getCurrentDirection();
    

private:
    float speed = 300.f;
    float size = 2.f;

    Direction currentDirection;
    
    sf::RenderWindow& window;
    sf::Texture texture;
    sf::Sprite sprite;
    
};

#endif
