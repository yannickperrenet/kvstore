# Single-threaded, in-memory, key-value store

* Exposes server to add and delete keys
* Server is single-threaded
* Key-value pairs are stored in-memory and are never written to disk
* R/W on store are all done sequentially

What can you store? Bytes.

Initial implementation:
* Keys have size of `char *`
* Values have size of `char *`

Next levels of difficulty:
* Tests
* Error handling
* Values can have much larger size. The bitcask value can come in here to describe a format for the
  memory
* Hashmap to store keys (that map to values entries of bitcask paper that then map to locations in
  memory)
* Expose via HTTP server that listens on port to receive requests for updating/inserting or
  retrieving keys.

Specification:
* #keys you can store
* #bytes for store (only counting the bytes of the values that are stored)

References:
* https://c-faq.com/
* https://riak.com/assets/bitcask-intro.pdf
* [Hashmap](https://github.com/TheAlgorithms/C/blob/master/data_structures/dictionary/dict.c)
* https://cliutils.gitlab.io/modern-cmake/
* https://makefiletutorial.com/


## Writing tests

### Cmake
```
sudo apt remove cmake
pip install cmake

cmake -S . -B build

cmake --build build
cd build && ctest
# Alternatively you can run: make test
# Or when inside the build directory:
cmake --build . && ctest
```

## Mistakes I made along the way

-   Calling `C` from `C++` requires

    ```
    extern "C" {
    #include "myheaderinc.h"
    }
    ```

-   Having a `main` function declared in the module I want to test. This results in the test cases
    never being found.


