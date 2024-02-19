#include "camera.h"

Camera::Camera(sf::RenderWindow& window)
    : window(window), moveSpeed(200.f) {
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    active = true;
}

void Camera::Update(float deltaTime, const sf::Vector2f& playerPosition) {
    if(active)
    {
        view.setCenter(playerPosition);
    }
}

void Camera::setActive(bool b)
{
    active = b;
}
bool Camera::getActive()
{
    return active;
}

sf::View& Camera::getView() {
    return view;
}