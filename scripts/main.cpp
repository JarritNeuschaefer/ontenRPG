#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <player.h>

int main() {
    // Initialisierung des Spiels
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    bool cameraMoving = true;
    bool oPressed = false;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Game");
    float centerX = window.getSize().x / 2.f;
    float centerY = window.getSize().y / 2.f;

    sf::Clock clock;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    sf::Font font;
    font.loadFromFile("fonts/SHPinscher.otf");

    sf::Text text;
    text.setCharacterSize(20.f);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    Player player(window);

    sf::View view;
    view.setSize(1280.f, 720.f);
    view.setCenter(centerX, centerY);

    sf::RectangleShape rect(sf::Vector2f(gridSizeF, gridSizeF));
    rect.setPosition(centerX + 10.f, centerY + 10.f);
    rect.setFillColor(sf::Color::Cyan);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Ereignisbehandlung
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::O)
                oPressed = false;
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O && !oPressed) {
                cameraMoving = !cameraMoving;
                view.setCenter(player.getPosition());
                oPressed = true;
            }
        }

        // Aktualisierung
        float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);

        // Maus-Eingabe
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x >= 0.f) {
            mousePosGrid.x = mousePosView.x / gridSizeU;
        }
        if (mousePosView.y >= 0.f) {
            mousePosGrid.y = mousePosView.y / gridSizeU;
        }
        window.setView(window.getDefaultView());

        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
           << "window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
           << "view: " << mousePosView.x << " " << mousePosView.y << "\n"
           << "grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
        text.setString(ss.str());

        // Tastatureingabe
        if (cameraMoving) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view.move(-player.getSpeed() * deltaTime, 0.f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(player.getSpeed() * deltaTime, 0.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                view.move(0.f, -player.getSpeed() * deltaTime);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(0.f, player.getSpeed() * deltaTime);
            }
        }

        // Rendering
        window.clear();
        window.setView(view);
        // Spiellemente zeichnen
        window.draw(rect);
        player.draw();
        window.setView(window.getDefaultView());
        // UI zeichnen
        window.draw(text);
        window.display();
    }

    return 0;
}