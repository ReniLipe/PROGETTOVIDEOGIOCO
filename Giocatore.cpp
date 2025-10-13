#include "Giocatore.h"
#include <SFML/Window/Keyboard.hpp>

Giocatore::Giocatore(sf::Vector2f posizione, float velocita)
    : velocita(velocita) {
    forma.setSize({16.f, 16.f}); // metà cella
    forma.setFillColor(sf::Color::Cyan);
    forma.setPosition(posizione);
}

void Giocatore::aggiorna(float deltaTime, const MAPPA& mappa) {
    sf::Vector2f movimento{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movimento.y -= velocita * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movimento.y += velocita * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movimento.x -= velocita * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movimento.x += velocita * deltaTime;

    sf::Vector2f nuovaPosizione = forma.getPosition() + movimento;
    sf::Vector2f size = forma.getSize();

    auto cellaDaPixel = [&](sf::Vector2f pos) -> sf::Vector2i {
        return sf::Vector2i(
            static_cast<int>(pos.x / mappa.getDimensioneCella()),
            static_cast<int>(pos.y / mappa.getDimensioneCella())
        );
    };

    // Calcola i 4 angoli del rettangolo del giocatore
    std::vector<sf::Vector2f> angoli = {
        nuovaPosizione,
        {nuovaPosizione.x + size.x, nuovaPosizione.y},
        {nuovaPosizione.x, nuovaPosizione.y + size.y},
        {nuovaPosizione.x + size.x, nuovaPosizione.y + size.y}
    };

    bool tutteCamminabili = true;
    for (const auto& angolo : angoli) {
        sf::Vector2i cella = cellaDaPixel(angolo);
        if (!mappa.èCamminabile(cella)) {
            tutteCamminabili = false;
            break;
        }
    }

    if (tutteCamminabili)
        forma.setPosition(nuovaPosizione);
}

void Giocatore::draw(sf::RenderWindow& window) const {
    window.draw(forma);
}
sf::Vector2f Giocatore::getPosizione() const {
    return forma.getPosition();
}
