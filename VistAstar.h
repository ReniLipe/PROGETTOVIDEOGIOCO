#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <unordered_map>

class VistAstar {
public:
    VistAstar(const std::vector<std::vector<int>>& griglia, sf::Vector2i partenza);

    void calcolaPercorso();
    void disegnaPercorso(sf::RenderTarget& target, float tileSize);

    void gestisciInput();              // toggle con V
    bool devoDisegnare() const;       // stato del toggle

private:
    struct Nodo {
        sf::Vector2i posizione;
        float g, h;
        Nodo* padre;
        float f() const { return g + h; }
    };

    const std::vector<std::vector<int>>& griglia;
    sf::Vector2i partenza;
    sf::Vector2i destinazione;
    std::vector<sf::Vector2i> percorso;

    bool mostraPercorso = false;
    bool vPremuto = false;

    bool èValida(sf::Vector2i pos) const;
    std::vector<sf::Vector2i> adiacenti(sf::Vector2i pos) const;
    float distanza(sf::Vector2i a, sf::Vector2i b) const;
    sf::Vector2i trovaPortaPiuVicina() const;
};
