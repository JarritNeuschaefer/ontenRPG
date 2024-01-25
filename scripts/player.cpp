#include "player.h"

Player::Player(sf::RenderWindow& window)
    : window(window), speed(300.0f) {
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100.0f, 100.0f);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw() {
    window.draw(shape);
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