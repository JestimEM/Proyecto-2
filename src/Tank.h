#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>

// Clase Tank que representa un tanque en el juego
class Tank {
public:
    enum class Color {
        BLUE,
        RED,
        CYAN,
        YELLOW
    };

    // Constructor y métodos del tanque
    Tank(Color tankColor, int gridX, int gridY, int id, int cellSize); // <-- cellSize añadido

    // Métodos "getter"
    int getGridX() const { return gridX; }
    int getGridY() const { return gridY; }
    Color getTankColor() const { return tankColor; }
    int getHitPoints() const { return hitPoints; }
    int getId() const { return id; }

    // Métodos para modificar el estado
    void setPosition(int gridX, int gridY);
    void takeDamage(int damage);

    // Otros métodos
    void draw(sf::RenderWindow &window, int cellSize) const;
    bool isDestroyed() const;


private:
    int gridX, gridY;  // Posición del tanque en el mapa
    Color tankColor;  // Color del tanque
    int hitPoints;  // Vida del tanque (100 por defecto)
    int id;  // ID único del tanque

    mutable sf::RectangleShape tankShape; // <-- mutable añadido

    void drawHealthBar(sf::RenderWindow &window, int cellSize) const; // Función auxiliar para la barra de vida
};

#endif