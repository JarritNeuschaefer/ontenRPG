#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

#include <player.h>
#include <camera.h>
#include <mouse.h>
#include <debug.h>

int main()
{
    // Initialisierung des Spiels
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    bool oPressed = false;
    bool pPressed = false;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Onten RPG");

    sf::Clock clock;
    MouseData mousedata;
    Player player(window);
    Camera cam(window);
    DebugWindow debugWindow(window);

    sf::RectangleShape rect(sf::Vector2f(gridSizeF, gridSizeF));
    rect.setPosition(window.getPosition().x / 2.f, window.getPosition().y / 2.f);
    rect.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Ereignisbehandlung
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::O)
                    oPressed = false;
                else if (event.key.code == sf::Keyboard::P)
                    pPressed = false;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::O && !oPressed)
                {
                    cam.setActive(!cam.getActive());
                    oPressed = true;
                }
                else if (event.key.code == sf::Keyboard::P && !pPressed)
                {
                    debugWindow.setActive(!debugWindow.getActive());
                    pPressed = true;
                }
            }
        }

        // Aktualisierung
        float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);
        cam.Update(deltaTime, player.getPosition());
        mousedata.update(deltaTime, cam, window, gridSizeU);
        debugWindow.update(mousedata);

        window.setView(window.getDefaultView());

        // Rendering
        window.clear();

        window.setView(cam.getView());
        // Spiellemente zeichnen
        window.draw(rect);
        player.draw();
        window.setView(window.getDefaultView());
        // UI zeichnen

        // window.draw(text);
        debugWindow.draw();
        window.display();
    }

    return 0;
}