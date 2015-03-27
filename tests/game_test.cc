#include <animal/animal_game.h>
#include <gtest/gtest.h>

class GameTests: ::testing::Test {
protected:
    slsBTree *tree = nullptr;

    virtual void SetUp() {
        tree = sls_animaltree_new();
        auto head = sls_animalnode_new(
            tree,
            SLS_FALSE,
            "hooves");
        auto leaf = sls_animalnode_new(
            tree,
            SLS_TRUE,
            "horse");
        tree->head = head;

    }
    virtual void TearDown() {

    }
}