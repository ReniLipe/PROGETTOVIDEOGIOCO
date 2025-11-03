#include <gtest/gtest.h>
#include "../MAPPA.h"

TEST(MappaTest, Dimensioni) {
    MAPPA m(32, 10, 20);
    EXPECT_EQ(m.getDimensioneCella(), 32);
}

TEST(MappaTest, CelleCamminabili) {
    MAPPA m(32, 5, 5);
    sf::Vector2i c = m.getCasellaCamminabileCasuale();
    
    EXPECT_GE(c.x, 0);
    EXPECT_GE(c.y, 0);
    EXPECT_LT(c.x, 5);
    EXPECT_LT(c.y, 5);
}

TEST(MappaTest, TipoCella) {
    MAPPA m(32, 5, 5);
    char t = m.getTipoCella(0,0);
    EXPECT_TRUE(t == '#' || t == '.' || t == 'D');
}
