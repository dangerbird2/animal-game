#include "inc.h"
#include <gtest/gtest.h>

class AnimalTests: public ::testing::Test {
protected:
    slsAnimalTree_t *tree = nullptr;

    virtual void SetUp() {
        tree = sls_animaltree_new();
    }

    virtual void TearDown() {
        sls_btree_destroy(tree);
    }
};

TEST_F(AnimalTests, AnimalTreeExists) {
    EXPECT_NE(nullptr, tree) << "tree should not be NULL"
}