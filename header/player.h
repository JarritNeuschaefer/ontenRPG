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
    void loadTextures(sf::RenderWindow& window);
    void changeTexture(int row, int coluomn);
    enum Direction {Up,Down,Left,Right};
    void setDirection(Direction newDirection);
    void prepare(sf::Sprite& sprite, sf::Texture& texture, sf::RenderWindow& window);
    Direction getCurrentDirection();
    

private:
    float speed = 3.f;
    float size = 2.f;

    Direction currentDirection;
    
    sf::RenderWindow& window;

    sf::Texture characterTexture;
    sf::Texture pantsTexture;
    sf::Texture shirtTexture;
    sf::Texture shoesTexture;
    sf::Texture hairTexture;

    sf::Sprite characterSprite;
    sf::Sprite pantsSprite;
    sf::Sprite shirtSprite;
    sf::Sprite shoesSprite;
    sf::Sprite hairSprite;

    
};

#endif
