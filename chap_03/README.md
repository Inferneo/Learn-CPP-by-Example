# Prime Guessing Game (C++20)

A small terminal game that generates a random 5-digit prime number and lets the user guess it with progressively richer clues.

## Features

* Generates a random prime between 1 and 99,999.
* Validates input safely using `std::optional`.
* Provides layered hints:

  * Rejects guesses ≥ 100000.
  * Indicates if the guess is not prime.
  * Shows digit feedback:

    * `*` = correct digit in correct position.
    * `^` = correct digit in wrong position.
    * `.` = digit not present.
* Uses `std::format`, lambdas, and `std::function`.
* Includes basic compile-time and runtime assertions.

## How It Works

1. A random number is generated until it satisfies `is_prime`.
2. The user repeatedly enters guesses.
3. Each guess is evaluated against a list of clue functions.
4. The first applicable clue is displayed.
5. The game ends when the correct number is guessed or input fails.

Digit checking is zero-padded to 5 digits to ensure consistent comparison.

## Requirements

* C++20 compiler (for `std::format`)
* Standard library with `<format>` support

Example compile command (GCC 13+ or Clang 16+):

```bash
g++ -std=c++20 -O2 main.cpp -o prime_game
```

## Example Output

```
Guess the number.
>12345
12345 is wrong. Try again.
Not prime.
```

## Notes

* Prime checking is simple trial division up to √n.
* Randomness is seeded with `std::random_device`.
* The design allows adding new clue lambdas without modifying the game loop.
