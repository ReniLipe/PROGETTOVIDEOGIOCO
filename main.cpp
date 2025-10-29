#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "MAPPA.h"
#include "Giocatore.h"
#include "VistAstar.h"
#include <memory>

int main() {
    const unsigned int larghezza = 1249;
    const unsigned int altezza = 739;
    const unsigned int dimensioneCella = 32;
    bool vittoria = false;

    sf::RenderWindow window(sf::VideoMode({larghezza, altezza}), "Labirinto con Stanze");
    window.setFramerateLimit(60);

    MAPPA mappa(dimensioneCella, larghezza, altezza);
    sf::Vector2i cellaIniziale = mappa.getCasellaCamminabileCasuale();
    sf::Vector2f posizionePixel(cellaIniziale.x * dimensioneCella, cellaIniziale.y * dimensioneCella);
    Giocatore giocatore(posizionePixel, 100.f); // velocità arbitraria

    // 🔧 Costruzione griglia logica per A*
    std::vector<std::vector<int>> griglia;
    for (int y = 0; y < altezza / dimensioneCella; ++y) {
        std::vector<int> riga;
        for (int x = 0; x < larghezza / dimensioneCella; ++x) {
            char tipo = mappa.getTipoCella(x, y);
            if (tipo == 'F') riga.push_back(0);
            else if (tipo == 'P') riga.push_back(2);
            else riga.push_back(1);
        }
        griglia.push_back(riga);
    }

    sf::Vector2i cellaGiocatore = cellaIniziale;
    std::unique_ptr<VistAstar> astar = std::make_unique<VistAstar>(griglia, cellaGiocatore);
    astar->calcolaPercorso();

    sf::Clock clock;

    sf::Font font;
    if (font.openFromFile("assets/arial-font/arial.ttf")) {
        // errore
    }
    sf::Text testoVittoria(font, "YOU WIN!", 50);
    testoVittoria.setFillColor(sf::Color::Cyan);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        if (!vittoria) {
            giocatore.aggiorna(deltaTime, mappa);
        }
        if (!vittoria) {
            sf::Vector2i cellaCorrente(
                static_cast<int>(giocatore.getPosizione().x) / dimensioneCella,
                static_cast<int>(giocatore.getPosizione().y) / dimensioneCella
            );

            if (mappa.getSimboloCasella(cellaCorrente) == 'P') {
                vittoria = true;
            }
        }

        // 🔄 Calcolo cella attuale del giocatore
        sf::Vector2f posPixel = giocatore.getPosizione();
        sf::Vector2i nuovaCella(
            static_cast<int>(posPixel.x) / dimensioneCella,
            static_cast<int>(posPixel.y) / dimensioneCella
        );

        if (nuovaCella != cellaGiocatore) {
            cellaGiocatore = nuovaCella;
            astar = std::make_unique<VistAstar>(griglia, cellaGiocatore);
            astar->calcolaPercorso();
        }

        astar->gestisciInput(); // ✅ toggle con tasto V

        window.clear();
        mappa.draw(window);
        giocatore.draw(window);

        if (astar->devoDisegnare())
            astar->disegnaPercorso(window, static_cast<float>(dimensioneCella));

        if (vittoria) {
            window.draw(testoVittoria);
        }

        window.display();
    }

    return 0;
}
