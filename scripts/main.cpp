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
    const int mapSizeX = 100;
    const int mapSizeY = 70;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    bool oPressed = false;
    bool pPressed = false;

    int fromX = 0;
    int toX = 0;
    int fromY = 0;
    int toY = 0;


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Onten RPG");
    window.setFramerateLimit(60);

    sf::Clock clock;
    MouseData mousedata;
    Player player(window);
    Camera cam(window);
    DebugWindow debugWindow(window);

    //game elements
    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape rect(sf::Vector2f(gridSizeF, gridSizeF));
    rect.setPosition(0.f, 0.f);
    rect.setFillColor(sf::Color::Cyan);
    //sf::RectangleShape tileMap[mapSizeX][mapSizeY];
    std::vector<std::vector<sf::RectangleShape>> tileMap;
    tileMap.resize(mapSizeX, std::vector<sf::RectangleShape>());
    
    for(int x = 0; x < mapSizeX; x++)
    {
        tileMap[x].resize(mapSizeY, sf::RectangleShape());
        for(int y = 0; y < mapSizeY; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setOutlineThickness(1.f);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
        }
    }

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

        tileSelector.setPosition(mousedata.getGridPos().x * gridSizeF, mousedata.getGridPos().y * gridSizeF);

        window.setView(window.getDefaultView()); // Rendering Here
        window.clear();

        window.setView(cam.getView()); // Render Game Elements

        fromX = cam.getView().getCenter().x / gridSizeF - 7;
        toX = cam.getView().getCenter().x / gridSizeF + 8;
        fromY = cam.getView().getCenter().y / gridSizeF - 4;
        toY = cam.getView().getCenter().y / gridSizeF + 5;

        if(fromX < 0) fromX = 0;
        else if(fromX >= mapSizeX) fromX = mapSizeX - 1;
        if(toX < 0) toX = 0;
        else if(toX >= mapSizeX) toX = mapSizeX - 1;
        if(fromY < 0) fromY = 0;
        else if(fromY >= mapSizeY) fromY = mapSizeY - 1;
        if(toY < 0) toY = 0;
        else if(toY >= mapSizeY) toY = mapSizeY - 1;

        for(int x = fromX; x < toX; x++)
            {
                for(int y = fromY; y < toY; y++)
                {
                    window.draw(tileMap[x][y]);
                }
            }
        window.draw(rect);
        window.draw(tileSelector);
        player.draw();


        window.setView(window.getDefaultView()); // Render UI

        debugWindow.draw();
        window.display();
    }

    return 0;
}