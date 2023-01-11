# Single-threaded, in-memory, key-value store

* Exposes server to add and get keys
* Server is single-threaded
* Key-value pairs are stored in-memory and are never written to disk
* R/W on store are all done sequentially

What can you store? Bytes. ASCII only.

Caveats:
* Updating the value of an existing key will reduce available store size as the old value is not
  removed from memory. Instead all values are appended to a buffer in memory and the key simply
  points to the new location in the buffer.

Initial implementation:
* Keys have a constant, hard-coded, maximum size.

Next levels of difficulty:
- [x] Insert to overwrite value of existing key
- [x] Tests
- [x] Error handling
* Expose via HTTP server that listens on port to receive requests for inserting and retrieving keys.
- [x] Values can have much larger size. The bitcask value can come in here to describe a format for
  the memory
* Hashmap to store keys (that map to values entries of bitcask paper that then map to locations in
  memory)

Specification:
* #keys you can store
* #bytes for store (only counting the bytes of the values that are stored)

References:
* https://c-faq.com/
* https://riak.com/assets/bitcask-intro.pdf
* [Hashmap](https://github.com/TheAlgorithms/C/blob/master/data_structures/dictionary/dict.c)
* https://cliutils.gitlab.io/modern-cmake/
* https://makefiletutorial.com/
* [Rob Pike](http://doc.cat-v.org/bell_labs/pikestyle)
* https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html


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
