#include <SFML/Graphics.hpp>
#include "MAPPA.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Labirinto con Stanze");

    MAPPA mappa(40, 1280, 720);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        mappa.draw(window);
        window.display();
    }

    return 0;
}
