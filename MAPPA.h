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
