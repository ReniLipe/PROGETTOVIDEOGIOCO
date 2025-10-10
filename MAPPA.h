#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class MAPPA {
public:
    MAPPA(unsigned int cellSize, unsigned int width, unsigned int height);

    void draw(sf::RenderWindow& window) const;
    sf::Vector2i getCasellaCamminabileCasuale() const;
    bool èCamminabile(sf::Vector2i cella) const;
    int getDimensioneCella() const;

private:
    void generateDungeon();
    void carveLabyrinth(int startX, int startY);
    void addRooms(int count);
    void placeDoors();

    unsigned int cellSize;
    unsigned int cols;
    unsigned int rows;
    std::vector<std::vector<char>> layout;
};
