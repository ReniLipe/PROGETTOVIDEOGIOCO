#include <gtest/gtest.h>
#include "../VistAstar.h"

TEST(AStarTest, Creazione) {
    std::vector<std::vector<int>> grid = {
        {0,0,0},
        {0,1,0},
        {0,0,0}
    };

    VistAstar a(grid, {0,0});
    EXPECT_FALSE(a.devoDisegnare());
}

TEST(AStarTest, ToggleDisegno) {
    std::vector<std::vector<int>> grid = {
        {0,0},
        {0,0},
    };

    VistAstar a(grid, {0,0});

    // simulate press V
    a.gestisciInput(); 
    EXPECT_TRUE(a.devoDisegnare());

    a.gestisciInput(); 
    EXPECT_FALSE(a.devoDisegnare());
}
