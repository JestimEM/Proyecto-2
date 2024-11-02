#include "Pathfinding.h"


#include "Map.h"


#include <queue>

#include <unordered_map> 

#include <algorithm>

#include <vector>

#include <random>


// Verifica si una posición está ocupada por otro tanque

bool isTankOccupied(int x, int y, const std::vector<Tank>& tanks) {

    for (const Tank& tank : tanks) {

        if (tank.getGridX() == x && tank.getGridY() == y) {

            return true;

        }

    }

    return false;

}


// Algoritmo de búsqueda en anchura (BFS) para encontrar una ruta

std::vector<Cell> bfs(const Map& map, int startX, int startY, int endX, int endY, const std::vector<Tank>& tanks) {

    std::queue<Cell> q;

    q.push({startX, startY});


    std::unordered_map<int, Cell> parent;

    parent[startY * map.getSize() + startX] = {-1, -1};


    std::vector<Cell> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; 


    while (!q.empty()) {

        Cell current = q.front();

        q.pop();


        if (current.x == endX && current.y == endY) {

            std::vector<Cell> path;

            for (Cell at = {endX, endY}; at.x != -1 && at.y != -1; at = parent[at.y * map.getSize() + at.x]) {

                path.push_back(at);

            }

            std::reverse(path.begin(), path.end());

            return path;

        }


        for (const Cell& dir : directions) {

            int newX = current.x + dir.x;

            int newY = current.y + dir.y;


            // Verificar límites, obstáculos y ocupación de tanques

            if (map.isWithinBounds(newX, newY) && !map.isObstacle(newX, newY) && 

                parent.find(newY * map.getSize() + newX) == parent.end() &&

                !isTankOccupied(newX, newY, tanks)) {


                q.push({newX, newY});

                parent[newY * map.getSize() + newX] = current;

            }

        }

    }


    return {}; // Ruta no encontrada

}


// Movimiento aleatorio de un tanque

std::vector<Cell> moveRandomly(int startX, int startY, const Map& map, const std::vector<Tank>& tanks) {

    std::vector<Cell> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::shuffle(directions.begin(), directions.end(), std::mt19937{std::random_device{}()});


    for (const Cell& dir : directions) {

        int newX = startX + dir.x;

        int newY = startY + dir.y;


        // Verificar límites, obstáculos y ocupación de tanques

        if (map.isWithinBounds(newX, newY) && !map.isObstacle(newX, newY) && !isTankOccupied(newX, newY, tanks)) {

            return {{startX, startY}, {newX, newY}};

        }

    }


    return {}; // No se encontró movimiento válido

}


// Algoritmo de Dijkstra para encontrar la ruta de menor costo

std::vector<Cell> dijkstra(const Map& map, int startX, int startY, int endX, int endY, const std::vector<Tank>& tanks) {

    using P = std::pair<int, Cell>;

    auto compare = [](const P& a, const P& b) {

        return a.first > b.first; 

    };

    std::priority_queue<P, std::vector<P>, decltype(compare)> pq(compare);


    std::unordered_map<int, int> cost;

    std::unordered_map<int, Cell> parent;


    int startKey = startY * map.getSize() + startX;

    cost[startKey] = 0;

    parent[startKey] = {-1, -1};

    pq.push({0, {startX, startY}});


    std::vector<Cell> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};


    while (!pq.empty()) {

        P current = pq.top();

        pq.pop();

        Cell currentCell = current.second;


        if (currentCell.x == endX && currentCell.y == endY) {

            std::vector<Cell> path;

            for (Cell at = {endX, endY}; at.x != -1 && at.y != -1; at = parent[at.y * map.getSize() + at.x]) {

                path.push_back(at);

            }

            std::reverse(path.begin(), path.end());

            return path;

        }


        for (const Cell& dir : directions) {

            int newX = currentCell.x + dir.x;

            int newY = currentCell.y + dir.y;

            int newKey = newY * map.getSize() + newX;


            // Verificar límites, obstáculos y ocupación de tanques

            if (map.isWithinBounds(newX, newY) && !map.isObstacle(newX, newY) && !isTankOccupied(newX, newY, tanks)) {

                int newCost = cost[currentCell.y * map.getSize() + currentCell.x] + 1;

                if (cost.find(newKey) == cost.end() || newCost < cost[newKey]) {

                    cost[newKey] = newCost;

                    parent[newKey] = currentCell;

                    pq.push({newCost, {newX, newY}});

                }

            }

        }

    }


    return {}; // Ruta no encontrada

}