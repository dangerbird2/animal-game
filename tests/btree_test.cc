extern "C" {
#include <animal/animal_game.h>
}
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

/*
mock callbacks for a binary tree
storing integers
*/
int mock_cmp(void const *a, void const *b) {
  const int *aa = (const int *)a;
  const int *bb = (const int *)b;
  int answer = 0;
  if (*aa > *bb) {
    answer = -1;
  } else if (*aa < *bb) {
    answer = 1;
  }
  return answer;
}

void *mock_copy(void const *val) {
  int *ival = new int[1];
  memcpy(ival, val, sizeof(int));
  return ival;
}

void mock_free(void *val) {
  printf("freeing node with val %d\n", *((int *)val));
  free(val);
}

namespace slsTest {

class BTreeTest : public ::testing::Test {
 protected:
  slsBTree *tree = nullptr;

  virtual void SetUp() { tree = sls_btree_new(mock_copy, mock_free); }

  virtual void TearDown() { sls_btree_destroy(tree); }
};

TEST_F(BTreeTest, TreeExists) {
  EXPECT_NE(tree, nullptr) << "this->tree should not be nullptr";
}

TEST_F(BTreeTest, MakeNode) {
  int i = 10;

  auto node = sls_bnode_new(tree, (void const *)&i, nullptr, nullptr);
  EXPECT_NE(node, nullptr);

  sls_bnode_destroy(node);
}

TEST_F(BTreeTest, MakeInvalidNode) {
  auto node = sls_bnode_new(nullptr, nullptr, nullptr, nullptr);
  EXPECT_EQ(NULL, node);
}

TEST_F(BTreeTest, AddNodeToTree) {
  int i = 10;
  int j = 11;

  auto nodeA = sls_bnode_new(tree, (void const *)&i, nullptr, nullptr);

  auto nodeB = sls_bnode_new(tree, (void const *)&j, nodeA, nullptr);
  tree->head = nodeB;
  /* ensure the tree links are correct */
  EXPECT_EQ(tree->head->left, nodeA);

  /* ensure values are actually copied*/
  EXPECT_NE(&i, nodeA->val);
}

/**
 * @brief Util test fixture
 * @details tests general utility functions in util.c
 */

class UtilTest : public ::testing::Test {
 protected:
  std::string str_a;
  std::string str_b;

  virtual void SetUp() {
    str_a = "foo bar \n biff";
    str_b = "y";
  }

  virtual void TearDown() {}
};

TEST_F(UtilTest, Teststralloc) {
  char *cpy_a = sls_stringalloc(str_a.c_str(), str_a.size() * sizeof(char));
  char *cpy_b = sls_stringalloc(str_b.c_str(), str_b.size() * sizeof(char));
  EXPECT_STREQ(str_a.c_str(), cpy_a);
  EXPECT_STREQ(str_b.c_str(), cpy_b);
  free(cpy_a);
  free(cpy_b);
}

TEST_F(UtilTest, TestResParse) {
  auto yes = std::vector<char const *>{"yes", "y", "Y", "YES", "yEs"};

  auto no = std::vector<char const *>{"no", "NO", "N", "n"};

  auto undef = std::vector<char const *>{"cow", "aegaewgaeg"};
  auto quit = std::vector<char const *>{"Q", "q", "Quit"};

  for (const auto &s : yes) {
    EXPECT_EQ(SLS_YES, sls_parse_response(s)) << s << " should return SLS_YES";
  }

  for (const auto &s : no) {
    EXPECT_EQ(SLS_NO, sls_parse_response(s)) << s << " should return SLS_NO";
  }

  for (const auto &s : undef) {
    EXPECT_EQ(SLS_UNDETERMINED, sls_parse_response(s))
        << s << " should return SLS_UNDETERMINED";
  }

  for (const auto &s : quit) {
    EXPECT_EQ(SLS_QUIT, sls_parse_response(s)) << s
                                               << " should return SLS_QUIT";
  }
}

/*
tests case-insensitive strcmp
*/
TEST_F(UtilTest, StrCmpTest) {
  const auto l = 100lu;
  auto valid_pairs = std::vector<int>{sls_strncmp_nocase("Q", "Q", l),
                                      sls_strncmp_nocase("Q", "q", l),
                                      sls_strncmp_nocase("Quit", "Quit", l),
                                      sls_strncmp_nocase("Quit", "QuiT", l),
                                      sls_strncmp_nocase("Quit", "QuiT", 1)};
  auto invalid_pairs = std::vector<int>{sls_strncmp_nocase("Quit", "QuiT ", l),
                                        sls_strncmp_nocase("Quit", " QuiT ", l),
                                        sls_strncmp_nocase("Quit", " QuiT ", l),
                                        sls_strncmp_nocase("no", " YES ", l),
                                        sls_strncmp_nocase("", "   ", l)};

  for (const auto &i : valid_pairs) {
    EXPECT_EQ(0, i);
  }
  for (const auto &i : invalid_pairs) {
    EXPECT_NE(0, i);
  }
}

}  // slsTest