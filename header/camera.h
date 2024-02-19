#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>

class Camera{
    public:
        Camera(sf::RenderWindow& window);
        void Update(float deltaTime, const sf::Vector2f& playerPosition);
        void setActive(bool b);
        bool getActive();
        sf::View& getView();
    private:
    sf::RenderWindow& window;
    sf::View view;
    float moveSpeed;
    bool active;
};

#endif