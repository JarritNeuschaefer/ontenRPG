#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <camera.h>

class Map
{
    public:
        Map(sf::RenderWindow& window);
        void draw(Camera cam);
        float getGridSizeF();
        unsigned getGridSizeU();
        void loadTextures();
        void transposeMap();
        void loadTilemapFromFile(const std::string& filename);
        int getIDFromTile(int x, int y);
        
    private:
        sf::RenderWindow& window;
        std::vector<std::vector<sf::Sprite>> tileMap;
        sf::Texture tilemapTexture;
        sf::Sprite tilemapSprite;
        std::vector<std::vector<sf::Texture>> textures;
        std::vector<std::vector<int>> mapData;
        float gridSizeF;
        unsigned gridSizeU;
        int mapSizeX = 30;
        int mapSizeY = 30;

        int sheetRows = 8;
        int sheetCols = 10;
        int fromX = 0;
        int toX = 0;
        int fromY = 0;
        int toY = 0;

};

#endif