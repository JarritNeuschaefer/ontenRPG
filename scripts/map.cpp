#include "map.h"

    Map::Map(sf::RenderWindow& window):window(window)
    {
        gridSizeF = 100.f;
        gridSizeU = static_cast<unsigned>(gridSizeF);
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
    }
    void Map::draw(Camera cam)
    {
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
    }
    float Map::getGridSizeF() {return gridSizeF;}
    unsigned Map::getGridSizeU() {return gridSizeU;}