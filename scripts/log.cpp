#include "log.h"

Log& Log::getInstance(sf::RenderWindow& window, float xPosition, float yPosition) {
    static Log instance(window, xPosition, yPosition);
    return instance;
}

Log::Log(sf::RenderWindow &window, float xPosition, float yPosition) 
: window(window), xPosition(xPosition),yPosition(yPosition), active(true)
{
    font.loadFromFile("fonts/SHPinscher.otf");

    text.setFont(font);
    text.setCharacterSize(15.f);
    text.setFillColor(sf::Color::White);
    text.setPosition(xPosition + 5.f, yPosition);

    sf::Color backgroundColor = sf::Color(0, 0, 0, 164);
    background.setSize(sf::Vector2f(400.f, 185.f));
    background.setFillColor(backgroundColor);
    background.setPosition(xPosition, yPosition);
    setActive(false);
}

void Log::write(std::string message)
{
    if (active)
    {
        messages.push_front(message);

        if (messages.size() > 10) {
            messages.pop_back();
        }

        std::stringstream ss;
        for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
            ss << *it << "\n";
            }
        debugText = ss.str();
    }
}

void Log::setActive(bool b)
{
    active = b;
}
bool Log::getActive()
{
    return active;
}

void Log::draw()
{
    if (active)
    {
        window.draw(background);
        text.setString(debugText);
        window.draw(text);
    }
}
