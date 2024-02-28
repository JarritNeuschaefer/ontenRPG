#ifndef DEBUG_H
#define DEBUG_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "mouse.h"
#include "player.h"

class DebugWindow
{
public:
    DebugWindow(sf::RenderWindow &window);
    void update(const MouseData md, Player player);
    void draw();
    void setActive(bool active);
    bool getActive();

private:
    sf::RenderWindow &window;
    bool active = false;
    std::string debugText;
    sf::Font font;
    sf::Text text;
};

#endif