#include "player.h"
#include <cmath>
#include <iostream>
#include <log.h>

// just for initialisation. stick to the default values
float elapsedAnimationTime = 0.0f;
int offset = 1;
int row = 0;
int coloumn = 0;
float animationSpeed = 3.5f;

// keychecks
static bool e_pressed = false;
static bool q_pressed = false;
static bool c_pressed = false;

// clothing
bool pants_on = true;
bool top_on = true;
bool shoes_on = true;
bool hair_on = true;

static bool wasKeyPressed[sf::Keyboard::KeyCount] = {false};

Player::Player(sf::RenderWindow &window)
    : window(window)
{
    loadTextures(window);
    setDirection(Down);
}

// gets and sets
float Player::getSpeed() const { return speed; }
sf::Vector2f Player::getPosition() const { return characterSprite.getPosition(); }
Player::Direction Player::getCurrentDirection() { return currentDirection; }
void Player::setDirection(Direction newDirection) { currentDirection = newDirection; }

// loads the Textures from the texture folder and prepares them
void Player::loadTextures(sf::RenderWindow &window)
{
    if (characterTexture.loadFromFile("texture/player_base.png"))
        prepare(characterSprite, characterTexture, window);
    else
        characterSprite.setColor(sf::Color::Magenta);
    if (topTexture.loadFromFile("texture/player_top.png"))
        prepare(topSprite, topTexture, window);
    else
        topSprite.setColor(sf::Color::Magenta);
    if (pantsTexture.loadFromFile("texture/player_pants.png"))
        prepare(pantsSprite, pantsTexture, window);
    else
        pantsSprite.setColor(sf::Color::Magenta);
    if (hairTexture.loadFromFile("texture/player_hair.png")) 
        prepare(hairSprite, hairTexture, window);
    else 
        hairSprite.setColor(sf::Color::Magenta);
    if (shoesTexture.loadFromFile("texture/player_shoes.png")) 
        prepare(shoesSprite, shoesTexture, window);
    else 
        shoesSprite.setColor(sf::Color::Magenta);
}

// makes sure, that the player and the clothes correctly set up
void Player::prepare(sf::Sprite &sprite, sf::Texture &texture, sf::RenderWindow &window)
{
    sprite.setTexture(texture);
    changeTexture(0, 0);
    sprite.setScale(size, size);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

// is used to determine wich Texture should be shown (e.g. for the walkcycle)
void Player::changeTexture(int row, int col)
{
    characterSprite.setTextureRect(sf::IntRect(row * 32, col * 64, 32, 64));
    topSprite.setTextureRect(sf::IntRect(row * 32, col * 64, 32, 64));
    pantsSprite.setTextureRect(sf::IntRect(row * 32, col * 64, 32, 64));
    hairSprite.setTextureRect(sf::IntRect(row * 32, col * 64, 32, 64));
    shoesSprite.setTextureRect(sf::IntRect(row * 32, col * 64, 32, 64));
}

void Player::update(float deltaTime)
{
    handleInput(deltaTime);
    animate(deltaTime);
}

void Player::draw()
{
    window.draw(characterSprite);
    if (hair_on)
        window.draw(hairSprite);
    if (top_on)
        window.draw(topSprite);
    if (pants_on)
        window.draw(pantsSprite);
    if(shoes_on) 
        window.draw(shoesSprite);
}

void Player::animate(float deltaTime)
{

    // will determine wich column should be read off, based on the direction.
    // 0: south, 1: east, 2: north (for west, east is just flipped)
    int row = 0;
    int column = 0;
    elapsedAnimationTime += deltaTime;

    switch (currentDirection)
    {
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
        topSprite.setScale(-size, size);
        pantsSprite.setScale(-size, size);
        shoesSprite.setScale(-size, size);
        break;
    case Right:
        column = 1;
        characterSprite.setScale(size, size);
        topSprite.setScale(size, size);
        pantsSprite.setScale(size, size);
        hairSprite.setScale(size, size);
        shoesSprite.setScale(size, size);
        break;
    }
    /*walkcycle-logic.
    offset: where the loop starts
    runAnimationLength: how many frames the run animation has
    elapsedAnimationTime / frameTime: speed of the animation
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {

        float frameTime = 1 / (animationSpeed * speed);
        int runAnimationLength = 8;
        row = static_cast<int>(elapsedAnimationTime / frameTime) % runAnimationLength + offset;
        changeTexture(column, row);
    }
    else
    {
        changeTexture(column, 0);
    }
}

void Player::handleInput(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movement.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movement.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movement.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movement.x += 1.f;
    }
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0.0f)
    {
        movement /= length;
    }
    /*key listeners
    E: shoes on/off
    Q: pants on/off
    C: top on/off
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !e_pressed)
    {
        e_pressed = true;
        print("E was pressed");
        shoes_on = !shoes_on;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && e_pressed)
    {
        e_pressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !q_pressed)
    {
        q_pressed = true;
        print("Q was pressed");
        pants_on = !pants_on;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && q_pressed)
    {
        q_pressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !c_pressed)
    {
        c_pressed = true;
        print("C was pressed");
        top_on = !top_on;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::C) && c_pressed)
    {
        c_pressed = false;
    }

    // actual movement of the character

    characterSprite.move(movement * (speed * 100.f) * deltaTime);
    topSprite.move(movement * (speed * 100.f) * deltaTime);
    pantsSprite.move(movement * (speed * 100.f) * deltaTime);
    hairSprite.move(movement * (speed * 100.f) * deltaTime);
    shoesSprite.move(movement * (speed * 100.f) * deltaTime);

    // direction determination for the walk cycle function
    if (movement.x < 0.0f) setDirection(Left);
    else if (movement.x > 0.0f) setDirection(Right);
    if (movement.y < 0.0f && movement.x == 0)setDirection(Up);
    else if (movement.y > 0.0f && movement.x == 0)setDirection(Down);
}