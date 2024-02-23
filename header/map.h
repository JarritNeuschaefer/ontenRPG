#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <camera.h>

class Map
{
    public:
        Map(sf::RenderWindow& window);
        void Update();
        void draw(Camera cam);
        float getGridSizeF();
        unsigned getGridSizeU();
        
    private:
        sf::RenderWindow& window;
        std::vector<std::vector<sf::RectangleShape>> tileMap;
        float gridSizeF;
        unsigned gridSizeU;
        const int mapSizeX = 100;
        const int mapSizeY = 70;
        int fromX = 0;
        int toX = 0;
        int fromY = 0;
        int toY = 0;

};

#endif