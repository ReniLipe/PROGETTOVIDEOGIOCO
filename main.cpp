#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window{sf::VideoMode{sf::Vector2u{800, 600}}, "Finestra SFML"};

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            // Chiudi se l'utente clicca sulla X
            if (event->is<sf::Event::Closed>())
                window.close();

            // Chiudi se l'utente preme ESC
            if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
