#include "Map.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp> 
#include <iostream>

Map::Map(int size) : size(size), connections(size * size, std::vector<int>(size * size, 0)) {
    std::srand(std::time(nullptr)); 
    loadTextures();
    generateObstacles(10); // Generar obstáculos después de cargar las texturas
    initializeConnections();
}

void Map::loadTextures() {
    if (!obstacleTexture.loadFromFile("/home/jestim/Escritorio/proyecto 2/src/imagenes/obstaculo.png")) {
        std::cerr << "Error al cargar la textura del obstáculo." << std::endl;
    }
    if (!emptyCellTexture.loadFromFile("/home/jestim/Escritorio/proyecto 2/src/imagenes/forest.jpg")) {
        std::cerr << "Error al cargar la textura de la celda vacía." << std::endl;
    }
}

void Map::generateObstacles(int percentage) {
    obstacleMap.clear(); // Limpiar obstáculos anteriores
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::rand() % 100 < percentage) {
                obstacleMap.insert({i, j}); // Insertar coordenadas del obstáculo en el conjunto
            }
        }
    }
}

bool Map::isObstacle(int x, int y) const {
    return obstacleMap.count({x, y}) > 0; // Verificar si las coordenadas están en el conjunto
}

bool Map::isWithinBounds(int x, int y) const {
    return x >= 0 && x < size && y >= 0 && y < size;
}

bool Map::isCellFree(int x, int y, const std::vector<Tank>& tanks) const {
    if (!isWithinBounds(x, y) || isObstacle(x, y)) {
        return false;
    }
    for (const Tank& tank : tanks) {
        if (tank.getGridX() == x && tank.getGridY() == y) {
            return false; 
        }
    }
    return true;
}

bool Map::isTankOccupied(int x, int y, const std::vector<Tank>& tanks) const {
    for (const Tank& tank : tanks) {
        if (tank.getGridX() == x && tank.getGridY() == y) {
            return true;
        }
    }
    return false;
}

int Map::getSize() const {
    return size;
}

void Map::draw(sf::RenderWindow& window, int cellSize) const {
    sf::Sprite cellSprite;  
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            cellSprite.setPosition(x * cellSize, y * cellSize);
            if (isObstacle(x, y)) {
                cellSprite.setTexture(obstacleTexture); 
            } else {
                cellSprite.setTexture(emptyCellTexture);
            }
            window.draw(cellSprite);
        }
    }
}

int Map::cellIndex(int x, int y) const {
    return y * size + x; 
}

void Map::initializeConnections() {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            if (!isObstacle(x, y)) {
                // Agregar conexiones a celdas adyacentes
                addConnection(x, y, x + 1, y);
                addConnection(x, y, x - 1, y);
                addConnection(x, y, x, y + 1);
                addConnection(x, y, x, y - 1);
            }
        }
    }
}

void Map::addConnection(int x1, int y1, int x2, int y2) {
    if (isWithinBounds(x2, y2) && !isObstacle(x2, y2)) {
        int index1 = cellIndex(x1, y1);
        int index2 = cellIndex(x2, y2);
        connections[index1][index2] = 1;
    }
}