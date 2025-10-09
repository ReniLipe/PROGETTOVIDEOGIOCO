#include "MAPPA.h"
#include <random>
#include <algorithm>
#include <stack>

MAPPA::MAPPA(unsigned int cellSize, unsigned int width, unsigned int height)
    : cellSize(cellSize), cols(width / cellSize), rows(height / cellSize) {
    generateDungeon();
}

void MAPPA::generateDungeon() {
    layout = std::vector<std::vector<char>>(rows, std::vector<char>(cols, 'W'));

    // Carving labirinto
    carveLabyrinth(1, 1);

    // Aggiungi stanze
    addRooms(5);

    // Aggiungi porte
    placeDoors();
}

void MAPPA::carveLabyrinth(int startX, int startY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::stack<std::pair<int, int>> stack;
    stack.push({startX, startY});
    layout[startY][startX] = 'F';

    std::vector<std::pair<int, int>> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        std::shuffle(directions.begin(), directions.end(), gen);
        bool carved = false;

        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx > 0 && ny > 0 && nx < cols - 1 && ny < rows - 1 && layout[ny][nx] == 'W') {
                layout[ny][nx] = 'F';
                layout[y + dy / 2][x + dx / 2] = 'F';
                stack.push({nx, ny});
                carved = true;
                break;
            }
        }

        if (!carved)
            stack.pop();
    }
}

void MAPPA::addRooms(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(1, cols - 5);
    std::uniform_int_distribution<> yDist(1, rows - 5);

    for (int i = 0; i < count; ++i) {
        int x = xDist(gen);
        int y = yDist(gen);

        for (int dy = 0; dy < 4; ++dy)
            for (int dx = 0; dx < 4; ++dx)
                layout[y + dy][x + dx] = 'F';
    }
}

void MAPPA::placeDoors() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> sides = {"top", "bottom", "left", "right"};
    std::shuffle(sides.begin(), sides.end(), gen);
    std::uniform_int_distribution<> posX(1, cols - 2);
    std::uniform_int_distribution<> posY(1, rows - 2);

    int placed = 0;
    for (const auto& side : sides) {
        if (placed >= 3) break;
        int pos = (side == "top" || side == "bottom") ? posX(gen) : posY(gen);

        if (side == "top" && layout[1][pos] == 'F') {
            layout[0][pos] = 'P';
            placed++;
        } else if (side == "bottom" && layout[rows - 2][pos] == 'F') {
            layout[rows - 1][pos] = 'P';
            placed++;
        } else if (side == "left" && layout[pos][1] == 'F') {
            layout[pos][0] = 'P';
            placed++;
        } else if (side == "right" && layout[pos][cols - 2] == 'F') {
            layout[pos][cols - 1] = 'P';
            placed++;
        }
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
