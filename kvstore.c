#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kvstore.h"

// Copies the string pointed to by `src` to the buffer pointed to by
// `dest` at location `at`.
// Returns a pointer to location `at` in `dest`.
char *strcpy_at(char *dest, const char *src, int at) {
    return strcpy(dest + at, src);
}

// Same as `strcmp` but at location `at` in `s1`.
int strcmp_at(const char *s1, const char *s2, int at) {
    return strcmp(s1 + at, s2);
}

void destroyStore(struct Store *store) {
    free(store->keys);
    store->keys = NULL;
    free(store->values);
    store->values = NULL;
    free(store->values_ptr);
    store->values_ptr = NULL;
}


// 0 (zero) means that the key is not yet initialized
struct Store initialize(int key_size, int num_keys, int storage_size) {
    struct Store store;
    store.key_size = key_size;
    store.num_keys = num_keys;
    store.values_total_size = storage_size;  // #chars it can store

    store.values_size = 0;  // offset in buffer

    store.keys = (char *)calloc(store.num_keys * store.key_size, 1);
    store.values_ptr = (char **)calloc(store.num_keys, sizeof(char *));
    store.values = (char *)malloc(store.values_total_size);

    if (store.keys == NULL || store.values == NULL) {
        destroyStore(&store);
        fprintf(stderr, "Failed to initialize store.\n");
        exit(INITIALIZATION_ERR);
    }

    return store;
}

// Gets the corresponding value of the given key from the store.
//
// Returns NULL if the key isn't found in the store.
char *get(struct Store *store, const char *key) {
    int size = store->key_size * store->num_keys;
    for (int i = 0; i < size; i+=store->key_size) {
        // TODO: use bcmp
        if (strcmp_at(store->keys, key, i) == 0) {
            return store->values_ptr[i];
        }
    }
    fprintf(stderr, "Key not present in store: %s\n", key);
    return NULL;
}

int insert(struct Store *store, const char *key, const char *value) {
    if (strlen(key)+1 > store->key_size) {
        fprintf(
            stderr,
            "Key size too large, max size is: %i\n", store->key_size
        );
        return KEY_SIZE_OVERFLOW;
    }
    int value_size = strlen(value) + 1;  // +1 for NUL byte
    if (value_size > store->values_total_size - store->values_size) {
        fprintf(stderr, "Not enough storage available to store given value.\n");
        return STORE_OUT_OF_STORAGE;
    }

    int size = store->num_keys * store->key_size;
    for (int i = 0; i < size; i+=store->key_size) {
        if (strcmp_at(store->keys, key, i) == 0 || store->keys[i] == 0) {
            strcpy_at(store->keys, key, i);

            // Store value.
            strcpy_at(store->values, value, store->values_size);
            store->values_ptr[i] = store->values + store->values_size;
            store->values_size += value_size;

            return 0;
        }
    }
    fprintf(stderr, "Could not insert item: store can't store more keys/values.\n");
    return STORE_FULL_ERR;
}
