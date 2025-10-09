#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MAPPA {
public:
    MAPPA(unsigned int cellSize = 40, unsigned int width = 1280, unsigned int height = 720);
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<std::vector<char>> layout;
    unsigned int cellSize;
    unsigned int cols, rows;
    void generateDungeon();
    void carveLabyrinth(int x, int y);
    void addRooms(int count);
    void placeDoors();
};
