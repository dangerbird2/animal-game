#include <animal/animal_game.h>
#include <gtest/gtest.h>

class GameTests : public ::testing::Test {
 protected:
  slsBTree *tree = nullptr;

  virtual void SetUp() {
    tree = sls_animaltree_new();
    auto head = sls_animalnode_new(tree, SLS_FALSE, (char *)"hooves");
    auto leaf = sls_animalnode_new(tree, SLS_TRUE, (char *)"horse");

    tree->head = head;    // a horse has hooves.
    leaf->parent = head;  // so I insert it as head->right
    head->right = leaf;
  }
  virtual void TearDown() { sls_btree_destroy(tree); }
};

TEST_F(GameTests, TestTraversalRight) {
  // "does your animal have hooves"
  auto yes_node =
      sls_attempt_traversal(tree->head, SLS_YES);  // should return "horse" leaf
  EXPECT_EQ(&(tree->head->right), yes_node);
}

TEST_F(GameTests, TestTraversalLeft) {
  auto no_node = sls_attempt_traversal(tree->head, SLS_NO);
  EXPECT_EQ(&(tree->head->left), no_node);
}
