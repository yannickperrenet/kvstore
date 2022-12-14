#include <stdio.h>
#include "kvstore.h"


int main(void) {
    // Create store that will be read and written to sequentially by
    // only one server.
    struct Store store = initialize();

    insert(&store, "10", "10");
    insert(&store, "11", "11");
    insert(&store, "11111111", "11");

    char *val;

    val = get(&store, "10");
    printf("Value for key %s: %s\n", "10", val);

    val = get(&store, "11");
    printf("Value for key %s: %s\n", "11", val);

    val = get(&store, "12");
    printf("Value for key %s: %s\n", "12", val);

    destroyStore(&store);

    // Start server
    //
}
