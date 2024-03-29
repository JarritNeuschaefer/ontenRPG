#include "info.h"

InfoWindow::InfoWindow(sf::RenderWindow &window) : window(window), active(false)
{
    font.loadFromFile("fonts/SHPinscher.otf");

    text.setFont(font);
    text.setCharacterSize(20.f);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(window.getSize().x - (window.getSize().x / 4.5f), 2.f);
}

void InfoWindow::update(MouseData md, Player player)
{
    if (active)
    {
        std::stringstream ss;
        ss << "Mouse Pos (Screen): " << md.getScreenPos().x << ", " << md.getScreenPos().y << "\n";
        ss << "Mouse Pos (Window): " << md.getWindowPos().x << ", " << md.getWindowPos().y << "\n";
        ss << "Mouse Pos (View): " << md.getViewPos().x << ", " << md.getViewPos().y << "\n";
        ss << "Mouse Pos (Grid): " << md.getGridPos().x << ", " << md.getGridPos().y << "\n";
        ss << "Direction: " << player.getCurrentDirection() << "\n";
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
        window.draw(text);
    }
}