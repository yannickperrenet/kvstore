#ifndef KVSTORE_H
#define KVSTORE_H

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

char *get(struct Store *store, char *key);

int insert(struct Store *store, char *key, char *value);

#endif
