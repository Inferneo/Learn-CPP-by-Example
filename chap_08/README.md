# Mind Reader (C++20 Coroutines)

A small C++20 experiment in prediction, state machines, and coroutines.

## Overview

This project implements a simple “pennies” game:

* The player repeatedly enters `0` or `1`.
* The machine attempts to predict the next input.
* If the machine predicts correctly, it wins the round.

Two approaches are included:

1. **Naive random predictor** — uniform random guesses.
2. **State-based mind reader** — tracks the last two outcomes and whether the player changed or repeated their choice, then predicts based on simple pattern matching.

A coroutine-based version models the game loop as a generator-like `Task` that yields `(player_choice, prediction)` pairs.

## Key Components

* `MindReader`
  Maintains a transition table keyed by:

  ```
  (previous_outcome, change_or_same, current_outcome)
  ```

  Updates state after each turn and predicts using recent behavioral patterns.

* `State`
  Stores a fixed lookup table for all possible state combinations.

* `Task`
  Custom coroutine type with:

  * `yield_value` for `(choice, prediction)`
  * Manual `next()` resumption
  * RAII destruction via `coro_deleter`

* `coroutine_mind_reader()`
  Drives the coroutine-based game loop.

## Requirements

* C++20 compiler with coroutine support.
* `<generator>` support (C++23 library or compatible implementation).

Tested with modern GCC/Clang builds using `-std=c++20` (or later).

## Build

```bash
g++ -std=c++20 -O2 main.cpp -o mind_reader
```

## Run

```bash
./mind_reader
```

Enter `0` or `1` repeatedly. Any other input exits.

## Notes

* Demonstrates:

  * Custom `std::hash` specialization.
  * Simple Markov-style behavioral modeling.
  * Manual coroutine plumbing (promise type, suspend points, handle destruction).
* `check_properties()` asserts that the initial state table has no hash bucket collisions.