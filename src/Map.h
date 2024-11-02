#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tank.h"
#include <SFML/Graphics.hpp> 
#include <set> // Para usar std::set

class Map {
public:
    Map(int size);

    void generateObstacles(int percentage);

    bool isObstacle(int x, int y) const;
    bool isTankOccupied(int x, int y, const std::vector<Tank>& tanks) const;
    bool isWithinBounds(int x, int y) const; 
    bool isCellFree(int x, int y, const std::vector<Tank>& tanks) const;

    int getSize() const;

    void draw(sf::RenderWindow& window, int cellSize) const;

    

private:
    int size;  
    std::set<std::pair<int, int>> obstacleMap; // Usando std::set para los obstáculos
    std::vector<std::vector<int>> connections; 

    sf::Texture obstacleTexture;
    sf::Texture emptyCellTexture;

    void loadTextures();
    int cellIndex(int x, int y) const;
    void initializeConnections();
    void addConnection(int x1, int y1, int x2, int y2); // Función auxiliar para conexiones
};

#endif