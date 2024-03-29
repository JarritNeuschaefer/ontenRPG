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

//clothing
bool pants_on = true;
bool shirt_on = true;
bool shoes_on = true;
bool hair_on = true;

static bool wasKeyPressed[sf::Keyboard::KeyCount] = {false};

Player::Player(sf::RenderWindow& window)
    : window(window) {
        loadTextures(window);
    }

void Player::loadTextures(sf::RenderWindow& window)
{
    if (characterTexture.loadFromFile("textur/character_sheet.png")) 
        prepare(characterSprite, characterTexture, window);
    else 
        characterSprite.setColor(sf::Color::Magenta);

    if (hairTexture.loadFromFile("textur/hair_1.png")) 
        prepare(hairSprite, hairTexture, window);
    else 
        hairSprite.setColor(sf::Color::Magenta);

    if (shirtTexture.loadFromFile("textur/shirt_1.png")) 
        prepare(shirtSprite, shirtTexture, window);
    else 
        shirtSprite.setColor(sf::Color::Magenta);

    if (pantsTexture.loadFromFile("textur/pants_1.png")) 
        prepare(pantsSprite, pantsTexture, window);
    else 
        pantsSprite.setColor(sf::Color::Magenta);

    if (shoesTexture.loadFromFile("textur/shoes_1.png")) 
        prepare(shoesSprite, shoesTexture, window);
    else 
        shoesSprite.setColor(sf::Color::Magenta);
}




void Player::prepare(sf::Sprite& sprite, sf::Texture& texture, sf::RenderWindow& window)
{
    sprite.setTexture(texture);
    changeTexture(0, 0);
    sprite.setScale(size, size);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

sf::Vector2f Player::getPosition() const {
    return characterSprite.getPosition();
}

void Player::changeTexture(int frame, int direction)
{
    characterSprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
    hairSprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
    shirtSprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
    pantsSprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
    shoesSprite.setTextureRect(sf::IntRect(frame * 32, direction * 64, 32, 64));
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
    animate(deltaTime);
}

void Player::draw() {
    window.draw(characterSprite);
    if(hair_on) window.draw(hairSprite);
    if(shirt_on) window.draw(shirtSprite);
    if(pants_on) window.draw(pantsSprite);
    if(shoes_on) window.draw(shoesSprite);
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
            characterSprite.setScale(-size, size);
            hairSprite.setScale(-size, size);
            shirtSprite.setScale(-size, size);
            pantsSprite.setScale(-size, size);
            shoesSprite.setScale(-size, size);
            break;
        case Right:
            column = 1;
            characterSprite.setScale(size, size);
            hairSprite.setScale(size, size);
            shirtSprite.setScale(size, size);
            pantsSprite.setScale(size, size);
            shoesSprite.setScale(size, size);
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
        print("E was pressed");
        shoes_on = !shoes_on;}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_pressed) {e_pressed = false;}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !q_pressed) {q_pressed = true;       
        print("Q was pressed");
        pants_on = !pants_on;}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && q_pressed) {q_pressed = false;}
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !c_pressed) {c_pressed = true;       
        print("C was pressed");
        shirt_on = !shirt_on;}
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C) && c_pressed) {c_pressed = false;}

characterSprite.move(movement * speed * deltaTime);
hairSprite.move(movement * speed * deltaTime);
shirtSprite.move(movement * speed * deltaTime);
pantsSprite.move(movement * speed * deltaTime);
shoesSprite.move(movement * speed * deltaTime);

if (movement.x < 0.0f) {setDirection(Left);} 
else if (movement.x > 0.0f) {setDirection(Right);}
if (movement.y < 0.0f   && movement.x == 0) {setDirection(Up);} 
else if (movement.y > 0.0f   && movement.x == 0) {setDirection(Down);}
    
}