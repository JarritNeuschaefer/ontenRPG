#include "player.h"
#include <cmath>
#include <iostream>
#include <log.h>

float elapsedAnimationTime = 0.0f;
int currentFrame = 0;
int row = 0;
int coloumn = 0;
int animationSpeed = 2;

//keychecks
static bool e_pressed = false;
static bool q_pressed = false;
static bool c_pressed = false;

static bool wasKeyPressed[sf::Keyboard::KeyCount] = {false};

Player::Player(sf::RenderWindow& window)
    : window(window) {    
if (texture.loadFromFile("textur/character_sheet.png")) 
    {
        sprite.setTexture(texture);
        changeTexture(0,0);
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
        sprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    }
else
    {
        sprite.setColor(sf::Color::Magenta);
    }
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::changeTexture(int frame, int direction)
{
    sprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
    animate(deltaTime);
}

void Player::draw() {
    window.draw(sprite);
}

float Player::getSpeed() const {
    return speed;
}


void Player::animate(float deltaTime)
{
    int row = 0;
    int column = 0;
    elapsedAnimationTime += deltaTime;

    switch (currentDirection) {
        case Up:
            column = 2;
            break;
        case Down:
            column = 0;
            break;
        case Left:
            column = 1;
            sprite.setScale(-size, size);
            break;
        case Right:
            column = 1;
            sprite.setScale(size, size);
            break;
    }
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

        int currentFrame = static_cast<int>(elapsedAnimationTime / (animationSpeed/10.f)) % 4;

        switch (currentFrame) {
            case 0:
            case 2:
                row = 0;
                break;

            case 1:
                row = 1;
                break;

            case 3:
                row = 2;
                break;
        }

        changeTexture(column, row);
    }
    else
    {
        changeTexture(column, 0);
    }
}


void Player::setDirection(Direction newDirection) {
    currentDirection = newDirection;
}
Player::Direction Player::getCurrentDirection()
{
    return currentDirection;
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { movement.y -= 1.f;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { movement.y += 1.f;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { movement.x -= 1.f;}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { movement.x += 1.f;}
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0.0f) 
        {
            movement /= length;
        }
    
    //key listeners
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !e_pressed) {e_pressed = true;       
        print("E was pressed");}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_pressed) {e_pressed = false;}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !q_pressed) {q_pressed = true;       
        print("Q was pressed");}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && q_pressed) {q_pressed = false;}
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !c_pressed) {c_pressed = true;       
        print("C was pressed");}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C) && c_pressed) {c_pressed = false;}

sprite.move(movement * speed * deltaTime);

if (movement.x < 0.0f) {setDirection(Left);} 
else if (movement.x > 0.0f) {setDirection(Right);}
if (movement.y < 0.0f   && movement.x == 0) {setDirection(Up);} 
else if (movement.y > 0.0f   && movement.x == 0) {setDirection(Down);}
    
}