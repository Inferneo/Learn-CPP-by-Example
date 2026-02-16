# Higher Lower With Jokers (C++20)

A small C++20 card game that implements a 54-card deck (52 standard cards + 2 jokers) and runs an interactive Higher/Lower guessing game in the terminal.

## Overview

The program:

* Defines `Suit`, `FaceValue`, `Card`, and `Joker` types.
* Uses `std::variant<Card, Joker>` to model an extended deck.
* Generates a standard 52-card deck.
* Extends it with two jokers.
* Shuffles using `std::mt19937` and `std::ranges::shuffle`.
* Runs an interactive loop where the player guesses whether the next card is higher or lower.

Jokers automatically count as a correct guess.

## Design

* Strong typing via `enum class` and a validated `FaceValue` (1–13).
* C++20 three-way comparison (`<=>`) for `Card` and `FaceValue`.
* `std::ranges` for deck generation, copying, and shuffling.
* `std::variant<Card, Joker>` for type-safe polymorphism.
* Overloaded stream operators for clean output.
* Lexicographic ordering of cards by `(FaceValue, Suit)`.

## Game Rules

* The deck is shuffled.
* You are shown the current card.
* Enter:

  * `h` → next card is higher
  * `l` → next card is lower
* If incorrect, the game ends and your score is printed.
* Jokers always count as correct.

## Example Output

```
9 of Spades: Next card higher (h) or lower (l)?
l
Ace of Hearts: Next card higher (h) or lower (l)?
h
8 of Spades: Next card higher (h) or lower (l)?
l
Next card was Jack of Hearts
You got 2 correct.
```

## Build

```bash
g++ -std=c++20 main.cpp playing_cards.cpp -o higher_lower
```

## Run

```bash
./higher_lower
```

## Structure

* `playing_cards.h` — Type definitions and declarations.
* `playing_cards.cpp` — Implementations and game logic.
* `main.cpp` — Entry point calling `higher_lower_with_jokers()`.
