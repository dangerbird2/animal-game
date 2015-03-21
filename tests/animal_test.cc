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
    EXPECT_NE(nullptr, tree) << "tree should not be NULL";
}

TEST_F(AnimalTests, CopyData) {
    auto dataA = sls_animal_new(SLS_FALSE, (char*)"cow");
    auto dataB = reinterpret_cast<slsAnimalData*>
        (sls_animal_copy(dataA));
    EXPECT_EQ(dataA->is_species, dataB->is_species);
    EXPECT_STREQ(dataA->description, dataB->description);

}