#include "player.h"

Player::Player(sf::RenderWindow& window)
    : window(window) {
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw() {
    window.draw(shape);
}

float Player::getSpeed() const {
    return speed;
}

void Player::handleInput(float deltaTime) {
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        shape.move(0.0f, -speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        shape.move(-speed * deltaTime, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        shape.move(0.0f, speed * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        shape.move(speed * deltaTime, 0.0f);
    }
    
}