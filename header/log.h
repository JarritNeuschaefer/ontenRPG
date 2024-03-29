#ifndef LOG_H
#define LOG_H


#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <list>

class Log
{
public:
    Log(sf::RenderWindow& window, float xPosition, float yPosition);
    static Log& getInstance(sf::RenderWindow& window, float xPosition, float yPosition);
    void write(std::string message);
    void draw();
    void setActive(bool active);
    bool getActive();

private:
    sf::RenderWindow &window;
    bool active = false;
    std::string debugText;
    sf::Font font;
    sf::Text text;
    float xPosition;
    float yPosition;
    std::list<std::string> messages;
    sf::RectangleShape background;
};

#define print(message) Log::getInstance(window, 10.f, (window.getSize().y - 200.f)).write(message)

#endif