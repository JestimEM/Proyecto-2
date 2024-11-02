#ifndef PATHFINDING_H

#define PATHFINDING_H


#include "Map.h"

#include "Tank.h"

#include <vector>


// Estructura que representa una celda del mapa

struct Cell {

    int x;

    int y;


    Cell() : x(0), y(0) {}

    Cell(int x_, int y_) : x(x_), y(y_) {}

};


// Funciones de búsqueda de rutas

std::vector<Cell> bfs(const Map& map, int startX, int startY, int endX, int endY, const std::vector<Tank>& tanks);

std::vector<Cell> moveRandomly(int startX, int startY, const Map& map, const std::vector<Tank>& tanks);

std::vector<Cell> dijkstra(const Map& map, int startX, int startY, int endX, int endY, const std::vector<Tank>& tanks);


#endif