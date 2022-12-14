#ifndef KVSTORE_H
#define KVSTORE_H


enum errors {
    INITIALIZATION_ERR = 1,
    STORE_FULL_ERR,
    KEY_SIZE_OVERFLOW,
    STORE_OUT_OF_STORAGE
};

char *strcpy_at(char *dest, const char *src, int at);

int strcmp_at(const char *s1, const char *s2, int at);

// Only needs to be able to store bytes as they are sent over the wire.
struct Store {
    char *keys;
    int key_size;
    int num_keys;
    char **values_ptr;
    char *values;
    int values_total_size;
    int values_size;  // offset in buffer
};

void destroyStore(struct Store *store);

struct Store initialize(void);

char *get(struct Store *store, const char *key);

int insert(struct Store *store, const char *key, const char *value);

#endif
