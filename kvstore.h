#ifndef KVSTORE_H
#define KVSTORE_H


enum errors {
    INITIALIZATION_ERR = 1,
    STORE_FULL_ERR,
    KV_SIZE_OVERFLOW
};

char *strcpy_at(char *dest, const char *src, int at);

int strcmp_at(const char *s1, const char *s2, int at);

// Only needs to be able to store bytes as they are sent over the wire.
struct Store {
    int key_size;
    int num_keys;
    char *keys;
    int values_total_size;
    int values_size;
    char **values_ptr;
    char *values;
};

void destroyStore(struct Store *store);

struct Store initialize(void);

char *get(struct Store *store, const char *key);

int insert(struct Store *store, const char *key, const char *value);

#endif
