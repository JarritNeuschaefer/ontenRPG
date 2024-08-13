#include "info.h"

InfoWindow::InfoWindow(sf::RenderWindow &window) : window(window), active(false)
{
    xPosition = window.getSize().x - (window.getSize().x / 4.5f);
    yPosition = 2.f;

    font.loadFromFile("fonts/SHPinscher.otf");

    text.setFont(font);
    text.setCharacterSize(20.f);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(xPosition, yPosition);

    sf::Color backgroundColor = sf::Color(0, 0, 0, 164);
    background.setSize(sf::Vector2f(260.f, 230.f));
    background.setFillColor(backgroundColor);
    background.setPosition(xPosition, yPosition);
}

void InfoWindow::update(MouseData md, Player player, unsigned gridSizeU)
{
    if (active)
    {
        std::stringstream ss;
        ss << "Mouse Pos (Screen): " << md.getScreenPos().x << ", " << md.getScreenPos().y << "\n";
        ss << "Mouse Pos (Window): " << md.getWindowPos().x << ", " << md.getWindowPos().y << "\n";
        ss << "Mouse Pos (View): " << md.getViewPos().x << ", " << md.getViewPos().y << "\n";
        ss << "Mouse Pos (Grid): " << md.getGridPos().x << ", " << md.getGridPos().y << "\n";
        ss << "Direction: " << player.getCurrentDirection() << "\n";
        ss << "Player Position x: " << player.getPosition().x << "\n";
        ss << "Player Position y: " << player.getPosition().y << "\n";
        ss << "Player Grid Position x: " << (int)player.getPosition().x / gridSizeU << "\n";
        ss << "Player Grid Position y: " << ((int)player.getPosition().y + 46) / gridSizeU << "\n";
        debugText = ss.str();
    }
}

void InfoWindow::setActive(bool b)
{
    active = b;
}
bool InfoWindow::getActive()
{
    return active;
}

void InfoWindow::draw()
{
    if (active)
    {
        text.setString(debugText);
        window.draw(background);
        window.draw(text);
    }
}