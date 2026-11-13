# Figures Project

## Requirements

* CMake 3.xx+
* A C++ compiler with C++17 support

## Directory Layout

* `src/` -- Contains the library and the application
  * `Factories/` -- Library factory classes
  * `Figures/` -- Library figure classes
  * `InputMethods/` -- Library input method classes
  * `Registries/` -- Registry classes and the reflection-like function for registering input method and figure classes
* `test/` -- Contains the unit tests
  * `FactoryTests/` -- Tests for the factory classes
  * `FigureTests/` -- Tests for the figure classes
  * `InputMethodsTests/` -- Tests for the input method classes
  * `RegistryTests/` -- Tests for the registry classes

## Building the project

The project uses [Catch2](https://github.com/catchorg/Catch2) for unit testing.
It fetches it from its GitHub repository.

If you need to build both the debug and release versions,
when using a multi-configuration generator (e.g., VS),
you can use a single CMake build directory for both configurations:

```bash
cmake -B build

# Debug
cmake --build build --config Debug
cmake --install build --config Debug

# Release
cmake --build build --config Release
cmake --install build --config Release
```

When using a single-configuration generator (e.g. Ninja),
you need separate build directories:

```bash
# Debug
cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
cmake --install build-debug

# Release
cmake -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
cmake --install build-release
```