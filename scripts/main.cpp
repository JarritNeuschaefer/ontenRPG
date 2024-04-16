#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

#include <player.h>
#include <camera.h>
#include <mouse.h>
#include <info.h>
#include <map.h>
#include <log.h>

int main()
{
    // Initialisierung des Spiels


    bool oPressed = false;
    bool pPressed = false;
    bool enterPressed = false;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Onten RPG");
    window.setFramerateLimit(60);

    sf::Clock clock;
    MouseData mousedata;
    Map map(window);
    Player player(window);
    Camera cam(window);
    InfoWindow infoWindow(window);
    Log::getInstance(window, 10.f, (window.getSize().y - 200.f));
    

    //game elements

    sf::RectangleShape tileSelector(sf::Vector2f(map.getGridSizeF(), map.getGridSizeF()));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    //cursor

    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromFile("textur/cursor.png")) { return EXIT_FAILURE; }
    sf::Cursor cursor;
    if (!cursor.loadFromPixels(cursorTexture.copyToImage().getPixelsPtr(), cursorTexture.getSize(), {0, 0})) { return EXIT_FAILURE;}
    window.setMouseCursor(cursor);

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
                if (event.key.code == sf::Keyboard::O && oPressed)
                {
                    oPressed = false;
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    pPressed = false;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    enterPressed = false;
                }
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
                    infoWindow.setActive(!infoWindow.getActive());
                    pPressed = true;
                }
                else if (event.key.code == sf::Keyboard::Enter && !enterPressed)
                {
                    Log::getInstance(window, 10.f, (window.getSize().y - 200.f)).setActive(!Log::getInstance(window, 10.f, (window.getSize().y - 200.f)).getActive());
                    enterPressed = true;
                }
            }
        }


        // Aktualisierung
        float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);
        cam.Update(deltaTime, player.getPosition());
        mousedata.update(deltaTime, cam, window, map.getGridSizeU());
        infoWindow.update(mousedata, player);

        tileSelector.setPosition(mousedata.getGridPos().x * map.getGridSizeF(), mousedata.getGridPos().y * map.getGridSizeF());

        window.setView(window.getDefaultView()); // Rendering Here
        window.clear();

        window.setView(cam.getView()); // Render Game Elements

        map.draw(cam);
        window.draw(tileSelector);
        player.draw();

        window.setView(window.getDefaultView()); // Render UI

        infoWindow.draw();
        Log::getInstance(window, 10.f, (window.getSize().y - 200.f)).draw();
        window.display();
    }

    return 0;
}