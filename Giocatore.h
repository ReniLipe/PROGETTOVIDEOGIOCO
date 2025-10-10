#pragma once
#include <SFML/Graphics.hpp>
#include "MAPPA.h"

class Giocatore {
public:
    Giocatore(sf::Vector2f posizione, float velocita = 100.f);

    void aggiorna(float deltaTime, const MAPPA& mappa);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape forma;
    float velocita;
};
