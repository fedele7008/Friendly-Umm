# Friendly Umm...

This project is Toy project in C++ that compiles C like custom language called friendly-Umm language into
[umjunsik-lang](https://github.com/rycont/umjunsik-lang), that is one of [esoteric programming language](https://en.wikipedia.org/wiki/Esoteric_programming_language).

## Requirements

* `cmake` with version higher than 3.11
* `g++` or any other c++ compiler
* `make` or any other build tool (e.g. Ninja)
* `git`
* `python3` (needed for GTEST)

## Optional

* `doxygen` if you want to create documentation
* `graphviz` if you want to create documentation with UML diagram (requires `doxygen` too)

## How to configure

Run `cmake -B build` from project root directory to generate build directory

* If you also want to create documentation, run `cmake -B build -D BUILD_DOC=ON`
* If you also want to create documentation with UML diagram, run `cmake -B build -D BUILD_DOC=ON -D UML=ON`s

Then run `cmake --build build` to compile the project

* Additionally, run `cmake --build build --target doc` to generate documentation

Now you will have `artifact` directory in project root.

* `artifact/bin/` directory contains executable binaries of the project (compiled from `apps` directory)
* `artifact/lib/` directory contains c++ libraries for the project (compiled from `modules` directory)
* `artifact/test/` directory contains unit tests for the project
* `artifact/doc/` directory contains documentation for the project (only if you generated documentation).

To see the documentation, open `artifact/doc/html/index.html`.

If you are setting up the project on multiple profile, I recommend you to create withing `build` folder.
In common IDE with separate Debug and Release profiles, set Debug profile to be built on `build/debug` and
let Release profile to be built on `build/release`. Then the git will automatically ignore both build profiles.

