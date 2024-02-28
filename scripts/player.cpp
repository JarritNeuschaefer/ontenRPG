#include "player.h"

float elapsedAnimationTime = 0.0f;
int currentFrame = 0;
int row = 0;
int coloumn = 0;
int animationSpeed = 2;

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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0.0f, -speed * deltaTime);
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            setDirection(Up);
        }
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0.0f, speed * deltaTime);

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            setDirection(Down);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-speed * deltaTime, 0.0f);
        setDirection(Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speed * deltaTime, 0.0f);
        setDirection(Right);
    }
    
}