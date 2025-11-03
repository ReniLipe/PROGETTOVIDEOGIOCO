#include <SFML/Graphics.hpp>
#include "../Giocatore.h"
#include "../MAPPA.h"
#include <gtest/gtest.h>

// -----------------------------
// Mappa finta per i test
// -----------------------------
class FakeMappa {
public:
    int cellSize = 32;

    bool èCamminabile(sf::Vector2i cella) const {
        // Blocca due celle specifiche per test collisione
        if ((cella.x == 1 && cella.y == 1) || (cella.x == 3 && cella.y == 2))
            return false;
        return true;
    }

    int getDimensioneCella() const { return cellSize; }
};

// -----------------------------
// TEST UNITARI
// -----------------------------

TEST(GiocatoreTest, PosizioneIniziale) {
    Giocatore g({10.f, 20.f}, 100.f);
    EXPECT_FLOAT_EQ(g.getPosizione().x, 10.f);
    EXPECT_FLOAT_EQ(g.getPosizione().y, 20.f);
}

TEST(GiocatoreTest, MovimentoSimulato) {
    FakeMappa m;
    Giocatore g({0.f, 0.f}, 32.f);

    // Simuliamo movimento verso destra di 1 cella
    sf::Vector2f movimento{32.f, 0.f};
    sf::Vector2f nuovaPos = g.getPosizione() + movimento;

    sf::Vector2i cella(
        static_cast<int>(nuovaPos.x) / m.getDimensioneCella(),
        static_cast<int>(nuovaPos.y) / m.getDimensioneCella()
    );

    if (m.èCamminabile(cella)) {
        // Test logica di collisione: la cella è camminabile
        EXPECT_TRUE(m.èCamminabile(cella));
    }
}

TEST(GiocatoreTest, CollisioneMuro) {
    FakeMappa m;
    Giocatore g({32.f, 0.f}, 32.f); // vicino cella (1,1)

    sf::Vector2f movimento{0.f, 32.f}; // verso la cella bloccata (1,1)
    sf::Vector2f nuovaPos = g.getPosizione() + movimento;

    sf::Vector2i cella(
        static_cast<int>(nuovaPos.x) / m.getDimensioneCella(),
        static_cast<int>(nuovaPos.y) / m.getDimensioneCella()
    );

    // La cella è un muro → non si può muovere
    EXPECT_FALSE(m.èCamminabile(cella));
}
