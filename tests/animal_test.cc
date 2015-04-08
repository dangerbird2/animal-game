<<<<<<< HEAD
#include "../include/animal/animal_game.h"
#include "../extern/googletest/include/gtest/gtest.h"
=======
#include <animal/animal_game.h>
#include <gtest/gtest.h>
>>>>>>> parent of d1c97a2... added additional documentation

class AnimalTests : public ::testing::Test {
 protected:
  slsBTree *tree = nullptr;

  virtual void SetUp() { tree = sls_animaltree_new(); }

  virtual void TearDown() { sls_btree_destroy(tree); }
};

TEST_F(AnimalTests, AnimalTreeExists) {
  EXPECT_NE(nullptr, tree) << "tree should not be NULL";
}

TEST_F(AnimalTests, CopyData) {
  auto dataA = sls_animal_new(SLS_FALSE, (char *)"cow");
  auto dataB = (slsAnimalData *)(sls_animal_copy(dataA));
  EXPECT_EQ(dataA->is_species, dataB->is_species);
  EXPECT_STREQ(dataA->description, dataB->description);
}

TEST_F(AnimalTests, BuildTree) {}
