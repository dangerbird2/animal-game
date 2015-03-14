#include "inc.h"
#include <gtest/gtest.h>

extern "C" {
    int mock_cmp(void const *a, void const *b) {
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
}

namespace slsTest {

class BTreeTest: public ::testing::Test {
protected:

    slsBTree *tree = nullptr;

    virtual void SetUp() {
        tree = sls_btree_new(
            sizeof(int), 
            sizeof(int),
            mock_cmp,
            nullptr,
            nullptr);
    }

    virtual void TearDown() {
        sls_btree_destroy(tree);
    }
};

TEST_F(BTreeTest, TreeExists) {
    EXPECT_NE(tree, nullptr) << "this->tree should not be nullptr";
}

} // slsTest