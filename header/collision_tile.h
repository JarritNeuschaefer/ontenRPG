#pragma once
#include <SFML/Graphics.hpp>

class collision_tile {
    public:
        collision_tile();
        void draw(sf::RenderWindow& window);
    private:
        int width = 100;
        int height = 100;
        sf::RectangleShape tile;

};