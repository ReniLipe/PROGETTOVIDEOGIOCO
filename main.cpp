#include <SFML/Graphics.hpp>
#include "MAPPA.h"
#include "Giocatore.h"

int main() {
    const unsigned int larghezza = 1280;
    const unsigned int altezza = 720;
    const unsigned int dimensioneCella = 32;

    sf::RenderWindow window(sf::VideoMode({larghezza, altezza}), "Labirinto con Stanze");
    window.setFramerateLimit(60);

    MAPPA mappa(dimensioneCella, larghezza, altezza);
    sf::Vector2i cella = mappa.getCasellaCamminabileCasuale();
    sf::Vector2f posizioneGiocatore(cella.x * dimensioneCella, cella.y * dimensioneCella);
    Giocatore giocatore(posizioneGiocatore);

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        giocatore.aggiorna(deltaTime, mappa);

        window.clear();
        mappa.draw(window);
        giocatore.draw(window);
        window.display();
    }

    return 0;
}
