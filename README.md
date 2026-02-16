# Modern C++ Experiments

A collection of small, focused C++20/23 projects exploring modern standard library features, strong typing, generic programming, coroutines, `<chrono>`, `<ranges>`, and expressive design.

The projects are from Frances Buontempo's book "Learn C++ by Example" (Manning Publications, 2024).

## Projects Included

### 1. Pascal’s Triangle 

Generates, validates, and formats Pascal’s Triangle.

**Highlights**

* Iterative row generation
* Mathematical property validation
* Auto-width formatting
* Sierpiński-style odd visualization
* Clean separation of logic and presentation

Concepts: ranges, views, CTAD, formatting, runtime assertions.

---

### 2. Prime Guessing Game

A 5-digit prime guessing game with layered feedback.

**Highlights**

* Random prime generation
* Safe input via `std::optional`
* Composable clue system via lambdas
* Digit-position feedback (`*`, `^`, `.`)

Concepts: `std::function`, lambdas, formatting, basic runtime validation.

---

### 3. Chrono Countdown Demo 

Exploration of modern calendrical and time-zone features.

**Highlights**

* `year_month_day`, `sys_days`
* Custom duration types
* Compile-time time logic checks
* Time zone–aware countdowns
* ISO date parsing

Concepts: `<chrono>` calendars, duration arithmetic, constrained templates.

---

### 4. Higher Lower With Jokers

A 54-card higher/lower game using strong typing and variants.

**Highlights**

* `enum class` for suits and values
* Validated face value wrapper
* `std::variant<Card, Joker>`
* Lexicographic ordering via `<=>`
* Ranges-based deck generation

Concepts: algebraic data types, three-way comparison, shuffle algorithms.

---

### 5. Blob Race

Terminal animation of polymorphic “blobs” racing vertically.

**Highlights**

* Abstract base class with deleted copy/move
* Template-based random behavior
* `std::unique_ptr` ownership
* ANSI animation loop

Concepts: runtime polymorphism, RAII, templates, ownership semantics.

---

### 6. Smash

A word-combination game that merges overlapping words.

**Highlights**

* Prefix/suffix overlap detection
* CSV-backed dictionary
* `std::multimap` for multiple definitions
* Random sampling via `<ranges>`

Concepts: lexicographic bounds, generic overlap selection.

---

### 7. Mind Reader

A simple behavioral predictor for binary user input.

**Highlights**

* State transition table
* Custom coroutine type (`Task`)
* Manual promise/handle management
* Simple Markov-style modeling

Concepts: coroutines, hash specialization, suspend/resume mechanics.

---

### 8. Triangle Slot Machine

A console slot machine built on triangle numbers.

**Highlights**

* Per-reel shuffle
* Last-digit payout logic
* `std::variant` + `std::visit`
* `<execution>` parallel algorithms
* Fold expressions

Concepts: modern random facilities, compile-time constraints, range-based transforms.

## Requirements

* C++20 minimum
* C++23 recommended for full `<chrono>` and coroutine support
* Modern compiler (GCC 13+, Clang 16+, or MSVC with C++20/23 enabled)

Example:

```bash
g++ -std=c++23 -O2 main.cpp -o program
```

Each project directory contains its own build instructions if multiple translation units are required.


## Structure

Each project is self-contained, typically with:

* `main.cpp`
* Optional headers (`.h`)
* Implementation files (`.cpp`)
* Supporting data files (where needed)

