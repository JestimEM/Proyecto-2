#include "Tank.h"

// Constructor del tanque
Tank::Tank(Color tankColor, int gridX, int gridY, int id, int cellSize) // <-- cellSize añadido
    : gridX(gridX), gridY(gridY), tankColor(tankColor), hitPoints(100), id(id) {
    
    tankShape.setSize(sf::Vector2f(cellSize, cellSize)); // Inicializar la forma del tanque

    switch (tankColor) {
        case Color::BLUE:    tankShape.setFillColor(sf::Color::Blue); break;
        case Color::RED:     tankShape.setFillColor(sf::Color::Red); break;
        case Color::CYAN:    tankShape.setFillColor(sf::Color::Cyan); break;
        case Color::YELLOW:  tankShape.setFillColor(sf::Color::Yellow); break;
    }
}

// Dibujar el tanque en la ventana de juego
void Tank::draw(sf::RenderWindow& window, int cellSize) const {
    tankShape.setPosition(gridX * cellSize, gridY * cellSize); // Actualizar posición
    window.draw(tankShape); 

    drawHealthBar(window, cellSize);
}

// Función auxiliar para dibujar la barra de vida
void Tank::drawHealthBar(sf::RenderWindow& window, int cellSize) const {
    sf::RectangleShape healthBar(sf::Vector2f(cellSize, 5)); 
    healthBar.setPosition(gridX * cellSize, gridY * cellSize - 8);

    // Calcular el color de la barra de vida
    float healthPercentage = static_cast<float>(hitPoints) / 100.0f;
    sf::Color barColor(255 * (1 - healthPercentage), 255 * healthPercentage, 0); // Interpolación de color
    healthBar.setFillColor(barColor); 

    // Ajustar el tamaño de la barra de vida
    healthBar.setScale(healthPercentage, 1.0f);

    window.draw(healthBar);
}

// Aplicar daño al tanque
void Tank::takeDamage(int damage) {
    hitPoints -= damage;
    if (hitPoints < 0) {
        hitPoints = 0;
    }
}

// Verificar si el tanque ha sido destruido
bool Tank::isDestroyed() const {
    return hitPoints <= 0;
}

// Actualizar la posición del tanque
void Tank::setPosition(int gridX, int gridY) {
    this->gridX = gridX;
    this->gridY = gridY;
}