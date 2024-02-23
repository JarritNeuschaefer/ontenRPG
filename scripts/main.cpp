#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

#include <player.h>
#include <camera.h>
#include <mouse.h>
#include <debug.h>
#include <map.h>

int main()
{
    // Initialisierung des Spiels


    bool oPressed = false;
    bool pPressed = false;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Onten RPG");
    window.setFramerateLimit(60);

    sf::Clock clock;
    MouseData mousedata;
    Map map(window);
    Player player(window);
    Camera cam(window);
    DebugWindow debugWindow(window);

    //game elements
    sf::RectangleShape tileSelector(sf::Vector2f(map.getGridSizeF(), map.getGridSizeF()));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape rect(sf::Vector2f(map.getGridSizeF(), map.getGridSizeF()));
    rect.setPosition(0.f, 0.f);
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
        mousedata.update(deltaTime, cam, window, map.getGridSizeU());
        debugWindow.update(mousedata);

        tileSelector.setPosition(mousedata.getGridPos().x * map.getGridSizeF(), mousedata.getGridPos().y * map.getGridSizeF());

        window.setView(window.getDefaultView()); // Rendering Here
        window.clear();

        window.setView(cam.getView()); // Render Game Elements

        map.draw(cam);
        window.draw(rect);
        window.draw(tileSelector);
        player.draw();


        window.setView(window.getDefaultView()); // Render UI

        debugWindow.draw();
        window.display();
    }

    return 0;
}