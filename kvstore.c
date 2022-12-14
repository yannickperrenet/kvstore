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
}


// The int 0 (zero) means that the key is not yet initialized
struct Store initialize(void) {
    struct Store store;
    store.key_size = 8;
    store.num_keys = 5;
    store.keys = (char *)calloc(store.num_keys * store.key_size, 1);
    store.values = (char *)calloc(store.num_keys * store.key_size, 1);

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
            char *tmp = store->values;
            return tmp + i;
        }
    }
    fprintf(stderr, "Key not present in store: %s\n", key);
    return NULL;
}

int insert(struct Store *store, const char *key, const char *value) {
    if (strlen(key)+1 >= store->key_size || strlen(value)+1 >= store->key_size) {
        fprintf(
            stderr,
            "Key or value size too large,"
            " max size is: %i\n", store->key_size
        );
        return KV_SIZE_OVERFLOW;
    }

    int size = store->num_keys * store->key_size;
    for (int i = 0; i < size; i+=store->key_size) {
        if (strcmp_at(store->keys, key, i) == 0 || store->keys[i] == 0) {
            strcpy_at(store->keys, key, i);
            strcpy_at(store->values, value, i);
            return 0;
        }
    }
    fprintf(stderr, "Could not insert item: store already full\n");
    return STORE_FULL_ERR;
}
