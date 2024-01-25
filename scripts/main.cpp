#include <SFML/Graphics.hpp>
#include "player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

    Player player(window);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();  // Hier wird deltaTime deklariert

        player.update(deltaTime);

        window.clear();
        player.draw();
        window.display();
    }

    return 0;
}