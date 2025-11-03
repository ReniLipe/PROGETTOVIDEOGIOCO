#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Giocatore.h"
#include "../MAPPA.h"
#include <gtest/gtest.h>

// -----------------------------
// Mappa fake per i test
// -----------------------------
class FakeMappa : public MAPPA {
public:
    FakeMappa() : MAPPA(32, 5, 5) {}

    // metodo senza override per test
    bool eCamminabile(sf::Vector2i cella) const {
        // blocca alcune celle per test collisione
        if ((cella.x == 1 && cella.y == 1) || (cella.x == 3 && cella.y == 2))
            return false;
        return true;
    }

    int getTileSize() const { return getDimensioneCella(); }
};

// -----------------------------
// Classe derivata per test
// -----------------------------
class TestGiocatore : public Giocatore {
public:
    using Giocatore::Giocatore;

    // Forza il movimento senza accesso a membri privati
    void forzaMovimento(sf::Vector2f direzione, float deltaTime, const FakeMappa& mappa) {
        // Simuliamo il movimento: spostiamo il giocatore solo se la cella è camminabile
        sf::Vector2f posAttuale = getPosizione();
        sf::Vector2f nuovaPos = posAttuale + direzione * 100.f * deltaTime;

        sf::Vector2i cella(static_cast<int>(nuovaPos.x) / mappa.getTileSize(),
                            static_cast<int>(nuovaPos.y) / mappa.getTileSize());

        if (mappa.eCamminabile(cella)) {
            // Usare il metodo pubblico aggiorna per muovere
            // Creiamo una copia della mappa temporanea che è compatibile
            Giocatore::aggiorna(deltaTime, mappa);
        }
    }
};

// -----------------------------
// TEST CASES
// -----------------------------

TEST(GiocatoreTest, PosizioneIniziale) {
    TestGiocatore g({10.f, 20.f});
    EXPECT_FLOAT_EQ(g.getPosizione().x, 10.f);
    EXPECT_FLOAT_EQ(g.getPosizione().y, 20.f);
}

TEST(GiocatoreTest, MovimentoOrizzontale) {
    FakeMappa m;
    TestGiocatore g({0.f, 0.f});
    g.forzaMovimento({1.f, 0.f}, 1.0f, m); // destra

    auto pos = g.getPosizione();
    EXPECT_GT(pos.x, 0.f); // il giocatore si è mosso
}

TEST(GiocatoreTest, MovimentoVerticale) {
    FakeMappa m;
    TestGiocatore g({0.f, 0.f});
    g.forzaMovimento({0.f, 1.f}, 1.0f, m); // giù

    auto pos = g.getPosizione();
    EXPECT_GT(pos.y, 0.f); // il giocatore si è mosso
}

TEST(GiocatoreTest, MovimentoDiagonale) {
    FakeMappa m;
    TestGiocatore g({0.f, 0.f});
    g.forzaMovimento({1.f, 1.f}, 1.0f, m); // diagonale giù-destra

    auto pos = g.getPosizione();
    EXPECT_GT(pos.x, 0.f);
    EXPECT_GT(pos.y, 0.f);
}

TEST(GiocatoreTest, CollisioneMuro) {
    FakeMappa m;
    TestGiocatore g({32.f, 0.f}); // vicino muro (1,1)
    g.forzaMovimento({0.f, 1.f}, 1.0f, m); // giù verso muro

    auto pos = g.getPosizione();
    EXPECT_LE(pos.y, 32.f); // non entra nella cella muro

    // test muro alternativo
    g = TestGiocatore({96.f, 64.f}); // vicino muro (3,2)
    g.forzaMovimento({1.f, 0.f}, 1.0f, m); // destra verso muro
    pos = g.getPosizione();
    EXPECT_LE(pos.x, 128.f); // non entra nella cella muro
}
