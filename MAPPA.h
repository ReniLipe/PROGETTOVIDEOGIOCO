//
// Created by Utente on 09/10/2025.
//

#ifndef PROGETTOVIDEOGIOCO_MAPPA_H
#define PROGETTOVIDEOGIOCO_MAPPA_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MAPPA {
public:
    MAPPA(unsigned int cellSize = 50);
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<std::vector<char>> layout;
    unsigned int cellSize;
    void generateDungeon();
};

#endif //PROGETTOVIDEOGIOCO_MAPPA_H