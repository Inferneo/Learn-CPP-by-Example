# Blob Race (C++)

A small C++ program that simulates a vertical “race” between polymorphic blobs rendered in the terminal.

## Overview

* `Blob` is an abstract base class with:

  * `step()`
  * `total_steps() const`
* `StepperBlob` increments its position by a fixed amount.
* `RandomBlob` increments its position using a supplied generator and distribution.
* Blobs are stored as `std::unique_ptr<Blob>` to demonstrate runtime polymorphism and ownership semantics.
* The race is animated in the terminal using ANSI escape codes.

## Features

* Runtime polymorphism via virtual functions.
* Deleted copy and move operations on `Blob`.
* Template-based random behavior (`RandomBlob<T, U>`).
* Basic property checks using `static_assert` and `assert`.
* Simple terminal animation loop using `<chrono>` and `<thread>`.

## Build

Requires a C++20-compatible compiler.

```bash
g++ -std=c++20 -O2 main.cpp Race.cpp -o blob_race
```

Adjust file names as needed.

## Run

```bash
./blob_race
```

The program clears the terminal and animates blob movement for a fixed number of iterations.

## Design Notes

* `Blob` has a virtual destructor and is non-copyable.
* `RandomBlob` is fully generic over generator and distribution types.
* Ownership is explicit and exclusive via `std::unique_ptr`.
* Separation of interface (`Race.h`) and implementation (`Race.cpp`).
