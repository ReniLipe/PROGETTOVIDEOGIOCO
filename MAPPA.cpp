#include <random>
#include <algorithm>
#include "MAPPA.h"

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
