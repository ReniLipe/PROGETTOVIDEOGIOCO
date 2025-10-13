#include "VistAstar.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <functional>

VistAstar::VistAstar(const std::vector<std::vector<int>>& griglia, sf::Vector2i partenza)
    : griglia(griglia), partenza(partenza), destinazione(trovaPortaPiuVicina()) {}

bool VistAstar::èValida(sf::Vector2i pos) const {
    return pos.y >= 0 && pos.y < static_cast<int>(griglia.size()) &&
           pos.x >= 0 && pos.x < static_cast<int>(griglia[0].size()) &&
           (griglia[pos.y][pos.x] == 0 || griglia[pos.y][pos.x] == 2);
}

std::vector<sf::Vector2i> VistAstar::adiacenti(sf::Vector2i pos) const {
    std::vector<sf::Vector2i> vicini;
    for (auto dir : {sf::Vector2i{1,0}, {-1,0}, {0,1}, {0,-1}}) {
        sf::Vector2i nuovo = pos + dir;
        if (èValida(nuovo)) vicini.push_back(nuovo);
    }
    return vicini;
}

float VistAstar::distanza(sf::Vector2i a, sf::Vector2i b) const {
    return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

sf::Vector2i VistAstar::trovaPortaPiuVicina() const {
    sf::Vector2i migliore = partenza;
    float minCosto = std::numeric_limits<float>::max();

    for (int y = 0; y < static_cast<int>(griglia.size()); ++y) {
        for (int x = 0; x < static_cast<int>(griglia[0].size()); ++x) {
            if (griglia[y][x] != 2) continue;

            sf::Vector2i candidata{x, y};

            struct Nodo {
                sf::Vector2i pos;
                float g, h;
                Nodo* padre;
                float f() const { return g + h; }
            };

            auto hash = [](sf::Vector2i v) { return v.y * 10000 + v.x; };
            std::priority_queue<Nodo*, std::vector<Nodo*>, std::function<bool(Nodo*, Nodo*)>> openSet(
                [](Nodo* a, Nodo* b) { return a->f() > b->f(); });

            std::unordered_map<int, Nodo*> visitati;
            Nodo* inizio = new Nodo{partenza, 0, distanza(partenza, candidata), nullptr};
            openSet.push(inizio);
            visitati[hash(partenza)] = inizio;

            bool raggiungibile = false;
            float costoFinale = std::numeric_limits<float>::max();

            while (!openSet.empty()) {
                Nodo* corrente = openSet.top(); openSet.pop();

                if (corrente->pos == candidata) {
                    costoFinale = corrente->g;
                    raggiungibile = true;
                    break;
                }

                for (auto& vicino : adiacenti(corrente->pos)) {
                    int h = hash(vicino);
                    if (visitati.count(h)) continue;

                    Nodo* nuovo = new Nodo{vicino, corrente->g + 1, distanza(vicino, candidata), corrente};
                    visitati[h] = nuovo;
                    openSet.push(nuovo);
                }
            }

            for (auto& [_, nodo] : visitati) delete nodo;

            if (raggiungibile && costoFinale < minCosto) {
                minCosto = costoFinale;
                migliore = candidata;
            }
        }
    }

    return migliore;
}

void VistAstar::calcolaPercorso() {
    percorso.clear();
    struct Comparatore {
        bool operator()(Nodo* a, Nodo* b) const { return a->f() > b->f(); }
    };

    std::priority_queue<Nodo*, std::vector<Nodo*>, Comparatore> openSet;
    std::unordered_map<int, Nodo*> visitati;

    auto hash = [](sf::Vector2i v) { return v.y * 10000 + v.x; };

    Nodo* inizio = new Nodo{partenza, 0, distanza(partenza, destinazione), nullptr};
    openSet.push(inizio);
    visitati[hash(partenza)] = inizio;

    while (!openSet.empty()) {
        Nodo* corrente = openSet.top(); openSet.pop();

        if (corrente->posizione == destinazione) {
            while (corrente) {
                percorso.push_back(corrente->posizione);
                corrente = corrente->padre;
            }
            std::reverse(percorso.begin(), percorso.end());
            break;
        }

        for (auto& vicino : adiacenti(corrente->posizione)) {
            int h = hash(vicino);
            if (visitati.count(h)) continue;

            Nodo* nuovo = new Nodo{vicino, corrente->g + 1, distanza(vicino, destinazione), corrente};
            visitati[h] = nuovo;
            openSet.push(nuovo);
        }
    }

    for (auto& [_, nodo] : visitati) delete nodo;
}

void VistAstar::disegnaPercorso(sf::RenderTarget& target, float tileSize) {
    for (auto& pos : percorso) {
        sf::RectangleShape cella(sf::Vector2f(tileSize, tileSize));
        cella.setPosition(sf::Vector2f(pos.x * tileSize, pos.y * tileSize));
        cella.setFillColor(sf::Color::White);
        target.draw(cella);
    }
}

void VistAstar::gestisciInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
        if (!vPremuto) {
            mostraPercorso = !mostraPercorso;
            vPremuto = true;
        }
    } else {
        vPremuto = false;
    }
}

bool VistAstar::devoDisegnare() const {
    return mostraPercorso;
}
