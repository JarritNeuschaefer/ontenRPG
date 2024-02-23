#include "player.h"

Player::Player(sf::RenderWindow& window)
    : window(window) {

    if (!texture.loadFromFile("textur/spielfigur.png")) {

    }
    sprite.setTexture(texture);
    sprite.setScale(2.f, 2.f);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw() {
    window.draw(sprite);
}

float Player::getSpeed() const {
    return speed;
}

void Player::handleInput(float deltaTime) {
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0.0f, -speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-speed * deltaTime, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0.0f, speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speed * deltaTime, 0.0f);
    }
    
}