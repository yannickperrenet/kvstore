extern "C" {
#include "kvstore.h"
}

#include <gtest/gtest.h>

class StoreTest : public ::testing::Test {
    protected:

        /* void SetUp() override { */
        /*     insert(&store, "10", "10"); */
        /* } */

        void TearDown() {
            destroyStore(&store);
        }

        struct Store store = initialize();
};

TEST_F(StoreTest, GetPresentKey) {
    insert(&store, "10", "10");
    ASSERT_STREQ(get(&store, "10"), "10");

    insert(&store, "11", "11");
    ASSERT_STREQ(get(&store, "11"), "11");
}

TEST_F(StoreTest, UpdateExistingKey) {
    insert(&store, "10", "10");
    ASSERT_STREQ(get(&store, "10"), "10");

    insert(&store, "10", "11");
    ASSERT_STREQ(get(&store, "10"), "11");
}

TEST_F(StoreTest, NotPresentKey) {
    ASSERT_STREQ(get(&store, "10"), NULL);
}

TEST_F(StoreTest, InsertFullStore) {
    char *key;
    for (int i = 0; i < STORE_NUM_KEYS; i++) {
        sprintf(key, "%i", i);
        insert(&store, key, "value");
    }
    ASSERT_EQ(insert(&store, "key", "value"), STORE_FULL_ERR);
}

TEST_F(StoreTest, KeySizeOverflow) {
    int overflow_size = STORE_KEY_SIZE + 1;
    char cause_overflow[overflow_size];
    for (int i = 0; i <= overflow_size; i++) {
        cause_overflow[i] = ' ';
    }
    ASSERT_EQ(insert(&store, cause_overflow, "value"), KV_SIZE_OVERFLOW);
}
