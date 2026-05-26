# Simple-Integer-Hash

Teaching repository that provides a tiny C++ library for converting strings to **unsigned 64-bit integer hashes**.

## `IntegerHash`

`IntegerHash` stores a string and computes a cached 64-bit hash for it.

* `equals(std::string)` performs a **perfect string equality** check (byte-for-byte).
* `hash()` returns the cached `std::uint64_t` hash.

The hash is **non-cryptographic** (intended for teaching / hash tables). This hash is a variant of well-known implementations.  Specifically, it uses FNV-1a (64-bit).

## Build

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

Disable tests / example:

```sh
cmake -S . -B build \
  -DSIMPLE_INTEGER_HASH_BUILD_TESTING=OFF \
  -DSIMPLE_INTEGER_HASH_BUILD_EXAMPLE=OFF
```

## Use from another CMake project

There are two ways you can use this library from another CMake project.

### Option A: FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(SimpleIntegerHash
  GIT_REPOSITORY https://github.com/AbstractClassroom-CPP/Simple-Integer-Hash.git
  GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(SimpleIntegerHash)

target_link_libraries(your_target PRIVATE SimpleIntegerHash::simple_integer_hash)
```

### Option B: install + find_package

Install:

```sh
cmake -S . -B build
cmake --build build
cmake --install build --prefix /your/prefix
```

Then in a consumer project:

```cmake
find_package(SimpleIntegerHash CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE SimpleIntegerHash::simple_integer_hash)
```
