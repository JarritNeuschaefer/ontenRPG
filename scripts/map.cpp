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

    tileMap.resize(mapSizeY, std::vector<sf::Sprite>());
    for (int row = 0; row < mapSizeY; row++)
    {
        tileMap[row].resize(mapSizeX, sf::Sprite());
        for (int col = 0; col < mapSizeX; col++)
        {
            tileMap[row][col].setScale(gridSizeF / textures[0][0].getSize().x, gridSizeF / textures[0][0].getSize().y);
            tileMap[row][col].setPosition(col * gridSizeF, row * gridSizeF);
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

    tileMap.resize(mapSizeY);

    for (int row = 0; row < mapSizeY; row++)
    {
        tileMap[row].resize(mapSizeX);

        for (int col = 0; col < mapSizeX; col++)
        {
            int textureIndex;
            if (!(inputFile >> textureIndex))
            {
                std::cerr << "Error reading texture index from file: " << filename << std::endl;
                continue;
            }
            if (textureIndex >= 0 && textureIndex < sheetRows * sheetCols)
            {
                int rowIndex = textureIndex / sheetCols;
                int colIndex = textureIndex % sheetCols;
                tileMap[row][col].setTexture(textures[rowIndex][colIndex]);
            }
            else
            {
                std::cerr << "Invalid texture index in file: " << filename << " at position (" << row << ", " << col << ")" << std::endl;
            }
            std::cout << "Loaded texture index: " << textureIndex << " at position (" << row << ", " << col << ")" << std::endl;
        }
    }
    inputFile.close();
}

void Map::loadTextures()
{
    tilemapTexture.loadFromFile("texture/tilemap.png");
    textures.resize(sheetRows);
    for (int row = 0; row < sheetRows; row++)
    {
        textures[row].resize(sheetCols);
        for (int col = 0; col < sheetCols; col++)
        {
            textures[row][col].loadFromImage(tilemapTexture.copyToImage(), sf::IntRect(col * 32, row * 32, 32, 32));
        }
    }
}

void Map::draw(Camera cam)
{
    fromX = cam.getView().getCenter().x / gridSizeF - 7;
    toX = cam.getView().getCenter().x / gridSizeF + 7;
    fromY = cam.getView().getCenter().y / gridSizeF - 4;
    toY = cam.getView().getCenter().y / gridSizeF + 4;

    if(fromX < 0) fromX = 0;
    else if(fromX >= mapSizeX) fromX = mapSizeX - 1;
    if(toX < 0) toX = 0;
    else if(toX >= mapSizeX) toX = mapSizeX - 1;
    if(fromY < 0) fromY = 0;
    else if(fromY >= mapSizeY) fromY = mapSizeY - 1;
    if(toY < 0) toY = 0;
    else if(toY >= mapSizeY) toY = mapSizeY - 1;

    for (int row = fromY; row <= toY; row++)
    {
        for (int col = fromX; col <= toX; col++)
        {
            window.draw(tileMap[row][col]);
        }
    }
}

int Map::getIDFromTile(int x, int y)
{
    if (x >= 0 && x < mapSizeX && y >= 0 && y < mapSizeY) {
        const sf::Texture* texture = tileMap[y][x].getTexture();
        if (texture) {
            for (int i = 0; i < sheetRows; ++i) {
                for (int j = 0; j < sheetCols; ++j) {
                    if (texture == &textures[i][j]) {
                        return i * sheetCols + j;
                    }
                }
            }
        }
        return -1;
    } else {
        return -1;
    }
}
float Map::getGridSizeF() {return gridSizeF;}
unsigned Map::getGridSizeU() {return gridSizeU;}
