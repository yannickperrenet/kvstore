#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kvstore.h"

const int STORE_NUM_KEYS = 5;
// number of bytes per key, including termination byte
const int STORE_KEY_SIZE = 8;

// Copies the string pointed to by `src` to the buffer pointed to by
// `dest` at location `at`.
// Returns a pointer to location `at` in `dest`.
char *strcpy_at(char *dest, const char *src, int at) {
    while (at-- > 0) {
        dest++;
    }

    return strcpy(dest, src);
}

// Same as `strcmp` but at location `at` in `s1`.
int strcmp_at(const char *s1, const char *s2, int at) {
    while (at-- > 0) {
        s1++;
    }

    return strcmp(s1, s2);
}

void destroyStore(struct Store *store) {
    free(store->keys);
    store->keys = NULL;
    free(store->values);
    store->values = NULL;
}


// TODO:
// - Now the int 0 (zero) means that the key is not yet initialized
struct Store initialize(void) {
    struct Store store;
    // TODO: error handling
    // TODO: Wouldn't it be easier to just insert '\0' everywhere?
    store.keys = (char *)calloc(STORE_NUM_KEYS * STORE_KEY_SIZE, 1);
    store.values = (char *)calloc(STORE_NUM_KEYS * STORE_KEY_SIZE, 1);
    return store;
}

// TODO: What if the key is not actually present
char *get(struct Store *store, char *key) {
    int size = STORE_KEY_SIZE * STORE_NUM_KEYS;
    for (int i = 0; i < size; i+=STORE_KEY_SIZE) {
        // TODO: use bcmp
        if (strcmp_at(store->keys, key, i) == 0) {
            char *tmp = store->values;
            for (int j = i; j > 0; j--) {
                tmp++;
            }
            return tmp;
        }
    }
    printf("[ERROR] Key not present in store: %s\n", key);
    return NULL;
}

// TODO:
// - make into more generic `update`, e.g. inserting same key different
//   value.
int insert(struct Store *store, char *key, char *value) {
    if (strlen(key)+1 >= STORE_KEY_SIZE || strlen(value)+1 >= STORE_KEY_SIZE) {
        printf(
            "[ERROR] Key or value size too large,"
            " max size is: %i\n", STORE_KEY_SIZE
        );
        return 0;
    }

    int size = STORE_NUM_KEYS * STORE_KEY_SIZE;
    for (int i = 0; i < size; i+=STORE_KEY_SIZE) {
        if (store->keys[i] == 0) {
            strcpy_at(store->keys, key, i);
            strcpy_at(store->values, key, i);
            return 1;
        }
    }
    printf("[ERROR] Could not insert item: store already full\n");
    return 0;
}

/* int main(void) { */
/*     // Create store that will be read and written to sequentially by */
/*     // only one server. */
/*     struct Store store = initialize(); */

/*     insert(&store, "10", "10"); */
/*     insert(&store, "11", "11"); */
/*     insert(&store, "11111111", "11"); */

/*     char *val; */

/*     val = get(&store, "10"); */
/*     printf("Value for key %s: %s\n", "10", val); */

/*     val = get(&store, "11"); */
/*     printf("Value for key %s: %s\n", "11", val); */

/*     val = get(&store, "12"); */
/*     printf("Value for key %s: %s\n", "12", val); */

/*     destroyStore(&store); */

/*     // Start server */
/*     // */
/* } */
