#include <SFML/Graphics.hpp>
#include "MAPPA.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Dungeon");

    MAPPA mappa(50); // Celle da 50x50 pixel

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
