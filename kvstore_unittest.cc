extern "C" {
#include "kvstore.h"
}

#include <gtest/gtest.h>

class StoreTest : public ::testing::Test {
    protected:

        void SetUp() override {
            insert(&store, "10", "10");
        }

        void TearDown() {
            destroyStore(&store);
        }

        struct Store store = initialize();
};

TEST_F(StoreTest, GetPresentKey) {
    ASSERT_STREQ(get(&store, "10"), "10");
}

TEST_F(StoreTest, NotPresentKey) {
    ASSERT_STREQ(get(&store, "20"), NULL);
}

// Test cases:
// - Error handling done correctly?
// - Store is full
// - Inserting key that is too long
// - Updating existing key
