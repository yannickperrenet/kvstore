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

        struct Store store = initialize(8, 5, 100);
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

    // NOTE: This is an implementation detail.
    ASSERT_EQ(store.values_size, 6);
}

TEST_F(StoreTest, NotPresentKey) {
    ASSERT_STREQ(get(&store, "10"), NULL);
}

TEST_F(StoreTest, InsertMaxAmountOfKeys) {
    char key[store.key_size];
    for (int i = 0; i < store.num_keys; i++) {
        sprintf(key, "%i", i);
        ASSERT_EQ(insert(&store, key, "value"), 0);
    }
    ASSERT_EQ(insert(&store, "key", "value"), STORE_FULL_ERR);
}

TEST_F(StoreTest, KeySizeOverflow) {
    int overflow_size = store.key_size + 1;
    char cause_overflow[overflow_size];
    for (int i = 0; i <= overflow_size; i++) {
        cause_overflow[i] = ' ';
    }
    ASSERT_EQ(insert(&store, cause_overflow, "value"), KEY_SIZE_OVERFLOW);
}

TEST_F(StoreTest, OutOfStorrage) {
    char full[store.values_total_size];
    for (int i = 0; i < store.values_total_size-1; i++) {
        full[i] = 'a';
    }
    // TODO: The current implementation is hopelessly dependend on this
    // insertion. It should just write bytes and not care about a
    // terminating NUL byte. Dependend due to use of `strlen`
    full[store.values_total_size-1] = '\0';

    ASSERT_EQ(insert(&store, "key", full), 0);
    ASSERT_EQ(insert(&store, "10", "value"), STORE_OUT_OF_STORAGE);
}
