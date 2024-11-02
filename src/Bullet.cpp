#include "Bullet.h"
#include <cmath>
#include <cstdlib>  // Para rand()

// Función que verifica si la línea de vista está despejada usando un algoritmo básico de raycasting
bool isLineOfSightClear(int x1, int y1, int x2, int y2, const Map& map) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(std::abs(dx), std::abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float currentX = x1;
    float currentY = y1;

    for (int i = 0; i < steps; i++) {
        if (map.isObstacle(static_cast<int>(currentX), static_cast<int>(currentY))) {
            return false;  // Hay un obstáculo en la línea de vista
        }
        currentX += xIncrement;
        currentY += yIncrement;
    }

    return true;  // No se encontraron obstáculos, la línea de vista está despejada
}

Bullet::Bullet(int startX, int startY, int targetX, int targetY, int shooterId)
    : posX(startX), posY(startY), shooterId(shooterId) {
    // Calcular la dirección
    float dx = targetX - startX;
    float dy = targetY - startY;
    float length = std::sqrt(dx * dx + dy * dy);
    dirX = dx / length;
    dirY = dy / length;
}

// Método para dibujar la bala
void Bullet::draw(sf::RenderWindow& window, int cellSize) {
    sf::CircleShape bulletShape(cellSize / 6);  // Tamaño pequeño de la bala
    bulletShape.setFillColor(sf::Color::Black); // Color de la bala
    bulletShape.setPosition(posX * cellSize, posY * cellSize);
    window.draw(bulletShape);
}


// Método para actualizar la posición de la bala
void Bullet::moveBullet() {
    posX += dirX * speed;
    posY += dirY * speed;
}

// Método para verificar colisiones con tanques
void Bullet::checkTankCollision(std::vector<Tank>& tanks, bool& destroyBullet) {
    for (Tank& tank : tanks) {
        if (tank.getGridX() == static_cast<int>(posX) && tank.getGridY() == static_cast<int>(posY)) {
            if (tank.getId() != shooterId) {
                switch (tank.getTankColor()) {
                    case Tank::Color::BLUE:
                    case Tank::Color::CYAN:
                        tank.takeDamage(25); 
                        break;
                    case Tank::Color::RED:
                    case Tank::Color::YELLOW:
                        tank.takeDamage(50);  
                        break;
                }
                destroyBullet = true; 
                return;
            }
        }
    }
}

// Método para verificar colisiones con los bordes del mapa
void Bullet::checkBorderCollision(const Map& map) {
    if (posX < 0 || posY < 0 || posX >= map.getSize() || posY >= map.getSize()) {
        if (posX < 0 || posX >= map.getSize()) {
            dirX = -dirX; 
        }
        if (posY < 0 || posY >= map.getSize()) {
            dirY = -dirY;  
        }
    }
}

// Método para manejar colisiones con obstáculos
void Bullet::handleObstacleCollision(const Map& map) {
    if (!isLineOfSightClear(static_cast<int>(posX), static_cast<int>(posY), static_cast<int>(posX + dirX), static_cast<int>(posY + dirY), map)) {
        float randomAngle = (std::rand() % 90 - 45) * (M_PI / 180.0f); 
        float newDirX = dirX * std::cos(randomAngle) - dirY * std::sin(randomAngle);
        float newDirY = dirX * std::sin(randomAngle) + dirY * std::cos(randomAngle);
        dirX = newDirX;
        dirY = newDirY;
    }
}

// Método update principal, ahora llama a las funciones más pequeñas
void Bullet::update(const Map& map, std::vector<Tank>& tanks, bool& destroyBullet) {
    handleObstacleCollision(map);
    moveBullet();
    checkTankCollision(tanks, destroyBullet);
    checkBorderCollision(map);
}