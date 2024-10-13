#include "collision_tile.h"

// Konstruktor, der die Kachel initialisiert
collision_tile::collision_tile() {
    // Rechteck mit der festgelegten Breite und Höhe erstellen
    tile.setSize(sf::Vector2f(width, height));

    // Position festlegen (optional, z.B. (100, 100))
    tile.setPosition(1500.f, 500.f);

    // Farbe der Kachel festlegen (z.B. grün)
    tile.setFillColor(sf::Color::Green);
}

// Methode zum Zeichnen der Kachel
void collision_tile::draw(sf::RenderWindow& window) {
    // Kachel im übergebenen Fenster zeichnen
    window.draw(tile);
}