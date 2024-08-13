#ifndef INFO_H
#define INFO_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "mouse.h"
#include "player.h"
#include "map.h"

class InfoWindow
{
public:
    InfoWindow(sf::RenderWindow &window);
    void update(const MouseData md, Player player, unsigned gridSizeU);
    void draw();
    void setActive(bool active);
    bool getActive();

private:
    float xPosition;
    float yPosition;
    sf::RenderWindow &window;
    bool active = false;
    std::string debugText;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape background;
};

#endif