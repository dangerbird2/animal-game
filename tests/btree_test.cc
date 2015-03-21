#include "inc.h"
#include <gtest/gtest.h>


/*
mock callbacks for a binary tree
storing integers
*/
int mock_cmp(void const *a, void const *b)
{
    const int *aa = (const int*)a;
    const int *bb = (const int*)b;
    int answer = 0;
    if (*aa > *bb) {
        answer = -1;
    } else if (*aa < *bb) {
        answer = 1;
    }
    return answer;
}

void *mock_copy(void const *val)
{
    int *ival = new int[1];
    memcpy(ival, val, sizeof(int));
    return ival;
}

void mock_free(void *val)
{
    printf("freeing node with val %d\n", *((int*)val));
    free(val);
}


namespace slsTest {

class BTreeTest: public ::testing::Test {
protected:

    slsBTree *tree = nullptr;

    virtual void SetUp() {
        tree = sls_btree_new(
            mock_copy,
            mock_free);
    }

    virtual void TearDown() {
        sls_btree_destroy(tree);
    }
};

TEST_F(BTreeTest, TreeExists) {
    EXPECT_NE(tree, nullptr) << "this->tree should not be nullptr";
}

TEST_F(BTreeTest, MakeNode) {
    int i = 10;

    auto node = sls_bnode_new(
        tree,
        (void const*)&i,
        nullptr,
        nullptr);
    EXPECT_NE(node, nullptr);

    sls_bnode_destroy(node);
}

TEST_F(BTreeTest, MakeInvalidNode) {
    auto node = sls_bnode_new(
        nullptr,
        nullptr,
        nullptr,
        nullptr);
    EXPECT_EQ(NULL, node);
}


TEST_F(BTreeTest, AddNodeToTree) {
    int i = 10;
    int j = 11;

    auto nodeA = sls_bnode_new(
        tree,
        (void const*)&i,
        nullptr,
        nullptr);

    auto nodeB = sls_bnode_new(
        tree,
        (void const*)&j,
        nodeA,
        nullptr);
    tree->head = nodeB;
    /* ensure the tree links are correct */
    EXPECT_EQ(tree->head->left, nodeA);

    /* ensure values are actually copied*/
    EXPECT_NE(&i, nodeA->val);
}

} // slsTest