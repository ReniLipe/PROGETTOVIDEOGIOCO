#pragma once
#include <SFML/Graphics.hpp>
#include "MAPPA.h"

class Giocatore {
public:
    sf::Vector2f getPosizione() const;
    Giocatore(sf::Vector2f posizione, float velocita = 100.f);
    const sf::RectangleShape& getForma() const { return forma; }
    void aggiorna(float deltaTime, const MAPPA& mappa);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape forma;
    float velocita;
};
