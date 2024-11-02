#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tank.h"
#include <vector>

// Clase Bullet para representar la bala disparada por un tanque
class Bullet {
public:
    Bullet(int startX, int startY, int targetX, int targetY, int shooterId);

    void draw(sf::RenderWindow& window, int cellSize);

    void update(const Map& map, std::vector<Tank>& tanks, bool& destroyBullet);

private:
    float posX, posY; 
    float dirX, dirY;  
    float speed = 0.2f;  
    int shooterId; 

    // Nuevas funciones para dividir la función update
    void moveBullet();
    void checkTankCollision(std::vector<Tank>& tanks, bool& destroyBullet);
    void checkBorderCollision(const Map& map);
    void handleObstacleCollision(const Map& map); 
};

#endif