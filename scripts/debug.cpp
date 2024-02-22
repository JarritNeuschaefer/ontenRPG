#include "debug.h"

DebugWindow::DebugWindow(sf::RenderWindow &window) : window(window), active(false)
{
    font.loadFromFile("fonts/SHPinscher.otf");

    text.setFont(font);
    text.setCharacterSize(20.f);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(window.getSize().x - (window.getSize().x / 4.5f), 2.f);
}

void DebugWindow::setActive(bool b)
{
    active = b;
}
bool DebugWindow::getActive()
{
    return active;
}

void DebugWindow::update(MouseData md)
{
    if (active)
    {
        std::stringstream ss;
        ss << "Mouse Pos (Screen): " << md.getScreenPos().x << ", " << md.getScreenPos().y << "\n";
        ss << "Mouse Pos (Window): " << md.getWindowPos().x << ", " << md.getWindowPos().y << "\n";
        ss << "Mouse Pos (View): " << md.getViewPos().x << ", " << md.getViewPos().y << "\n";
        ss << "Mouse Pos (Grid): " << md.getGridPos().x << ", " << md.getGridPos().y << "\n";
        debugText = ss.str();
    }
}

void DebugWindow::draw()
{
    if (active)
    {
        text.setString(debugText);
        window.draw(text);
    }
}