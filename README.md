# Most basic key-value store I could think of

> I don't expect anyone to use this piece of "software", I just wanted to play around a bit with
> the C programming language.

Details:
* Key-value pairs are stored in-memory and are never written to disk.
* Store is backed by an array and lookups are done by scanning the array (instead of using a
  HashMap).
* Keys/Values are not evicted and thus the store will eventually be full.
* All values are stored sequentially in one big memory buffer. When updating the value of a key, the
  old value is never removed and the new value is simply added to the back of the memory buffer
  (accompanied by an updated pointer for the key). This is similar to the
  [Bitcask paper](https://riak.com/assets/bitcask-intro.pdf).

Why you wouldn't want to actually be using this implementation:
* Keys/Values are never persisted on disk.
* When storing a large amount of keys, the lookup of those keys becomes considerably slow.
* No eviction policy.

Initialization of the store:
* #keys you can store
* #bytes for store (only counting the bytes of the values that are stored)

## Tests

```
# Install cmake
sudo apt remove cmake
pip install cmake

# Build and run tests
cmake --build build
cd build && ctest

# Alternatively you can run: make test
# Or when inside the build directory:
cmake --build . && ctest
```

## References
* [`comp.lang.c` Frequently Asked Questions](https://c-faq.com/)
* [Hashmap](https://github.com/TheAlgorithms/C/blob/master/data_structures/dictionary/dict.c)
* [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
* [Makefile tutorial](https://makefiletutorial.com/)
* [Rob Pike on ordering `includes` in C](http://doc.cat-v.org/bell_labs/pikestyle)
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/system-calls-or-bust.html)

## Mistakes I made along the way

-   Calling `C` from `C++` requires

    ```
    extern "C" {
    #include "myheaderinc.h"
    }
    ```

-   Having a `main` function declared in the module I want to test. This results in the test cases
    never being found.
