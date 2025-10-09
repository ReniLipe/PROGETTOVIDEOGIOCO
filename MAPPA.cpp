#include "MAPPA.h"
#include <random>
#include <algorithm>

MAPPA::MAPPA(unsigned int cellSize) : cellSize(cellSize) {
    generateDungeon();
}

void MAPPA::generateDungeon() {
    layout = std::vector<std::vector<char>>(10, std::vector<char>(10, 'W'));

    // Crea un corridoio centrale percorribile
    for (int y = 1; y < 9; ++y)
        for (int x = 1; x < 9; ++x)
            layout[y][x] = 'F';

    // Lati disponibili
    std::vector<std::string> sides = {"top", "bottom", "left", "right"};

    // Mescola e prendi 3 lati diversi
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(sides.begin(), sides.end(), gen);

    for (int i = 0; i < 3; ++i) {
        std::string side = sides[i];
        std::uniform_int_distribution<> dist(1, 8); // Evita angoli

        int pos = dist(gen);

        if (side == "top")       layout[0][pos] = 'P';
        else if (side == "bottom") layout[9][pos] = 'P';
        else if (side == "left")   layout[pos][0] = 'P';
        else if (side == "right")  layout[pos][9] = 'P';
    }
}

void MAPPA::draw(sf::RenderWindow& window) const {
    for (size_t y = 0; y < layout.size(); ++y) {
        for (size_t x = 0; x < layout[y].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
            cell.setPosition(sf::Vector2f(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize)));

            switch (layout[y][x]) {
                case 'W': cell.setFillColor(sf::Color::Black); break;
                case 'F': cell.setFillColor(sf::Color(128, 128, 128)); break;
                case 'P': cell.setFillColor(sf::Color::Green); break;
            }

            window.draw(cell);
        }
    }
}
