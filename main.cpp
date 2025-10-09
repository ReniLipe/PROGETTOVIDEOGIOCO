#include <SFML/Graphics.hpp>
#include "MAPPA.h"

int main() {
    sf::RenderWindow window{sf::VideoMode{sf::Vector2u{900, 500}}, "Dungeon"};

    MAPPA mappa;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        mappa.draw(window);
        window.display();
    }

    return 0;
}
