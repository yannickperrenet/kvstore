#ifndef KVSTORE_H
#define KVSTORE_H

extern const int STORE_NUM_KEYS;
// number of bytes per key, including termination byte
extern const int STORE_KEY_SIZE;

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
    char *keys;
    int value_size;
    char *values;
};

void destroyStore(struct Store *store);

struct Store initialize(void);

char *get(struct Store *store, const char *key);

int insert(struct Store *store, const char *key, const char *value);

#endif
