#include "map.h"
#include <iostream>
#include <fstream>
#include <algorithm>



Map::Map(sf::RenderWindow& window) : window(window)
    {
        gridSizeF = 100.f;
        gridSizeU = static_cast<unsigned>(gridSizeF);

        loadTextures();
        loadTilemapFromFile("mapdata/map1.txt");

        tileMap.resize(mapSizeX, std::vector<sf::Sprite>());
        for (int x = 0; x < mapSizeX; x++)
        {
            tileMap[x].resize(mapSizeY, sf::Sprite());
            for (int y = 0; y < mapSizeY; y++)
            {
                tileMap[x][y].setScale(gridSizeF / textures[0][0].getSize().x, gridSizeF / textures[0][0].getSize().y);
                tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
            }
        }
    }

    void Map::loadTilemapFromFile(const std::string& filename)
        {
            std::ifstream inputFile(filename);

            if (!inputFile.is_open())
            {
                std::cerr << "Error opening file: " << filename << std::endl;
                return;
            }

            tileMap.resize(mapSizeX);

            for (int x = 0; x < mapSizeX; x++)
            {
                tileMap[x].resize(mapSizeY);

                for (int y = 0; y < mapSizeY; y++)
                {
                    int textureIndex;
                    if (!(inputFile >> textureIndex))
                    {
                        std::cerr << "Error reading texture index from file: " << filename << std::endl;
                        continue;
                    }
                    if (textureIndex >= 0 && textureIndex < sheetSizeX * sheetSizeY)
                    {
                        tileMap[x][y].setTexture(textures[textureIndex % sheetSizeY][textureIndex / sheetSizeY]);
                    }
                    else
                    {
                        std::cerr << "Invalid texture index in file: " << filename << " at position (" << x << ", " << y << ")" << std::endl;
                    }
                    std::cout << "Loaded texture index: " << textureIndex << " at position (" << x << ", " << y << ")" << std::endl;
                }
            }
            inputFile.close();
        }


    void Map::loadTextures()
        {
            tilemapTexture.loadFromFile("textur/tilemap.png");
            textures.resize(sheetSizeX);
            for(int x = 0; x < sheetSizeX; x++)
            {
                textures[x].resize(sheetSizeY);
                for(int y = 0; y < sheetSizeY; y++)
                {
                    textures[x][y].loadFromImage(tilemapTexture.copyToImage(), sf::IntRect(x * 32, y * 32, 32, 32));
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

            for (int x = fromX; x <= toX; x++)
                {
                    for (int y = fromY; y <= toY; y++)
                        {
                            window.draw(tileMap[x][y]);
                        }
                }
        }
    
    float Map::getGridSizeF() {return gridSizeF;}
    unsigned Map::getGridSizeU() {return gridSizeU;}