# Pascal’s Triangle in Modern C++

A small C++20 program that generates, validates, and displays Pascal’s Triangle using modern standard library features (ranges, views, CTAD, `std::format`).

## Features

* Generates Pascal’s Triangle iteratively from previous rows.
* Validates mathematical properties:

  * First and last elements are 1.
  * Row size matches row index.
  * Row sum equals ( 2^n ).
  * Symmetry (palindromic rows).
  * No negative entries.
* Multiple display modes:

  * Left-justified numeric output.
  * Center-justified formatted output.
  * Auto-width formatting based on largest value.
  * Odd-number visualization (Sierpiński pattern) using `*`.

## Requirements

* C++20 or later.
* Compiler with support for:

  * `<ranges>`
  * `<format>`
  * Class Template Argument Deduction (CTAD)

### GCC Example

```bash
g++ -std=c++20 -O2 main.cpp -o pascal
```

### MSVC

Enable `/std:c++latest` or C++20 in project settings.

## Usage

Change the number of rows in `main()`:

```cpp
auto triangle = generate_triangle(16);
```

Recompile and run.

## Notes

* Integer overflow occurs around 36 rows due to `int` limits.
* Increase the numeric type (e.g., `long long`) for larger triangles.
* Formatting width must grow as values exceed four digits.

## Concepts Demonstrated

* Functional-style composition with ranges and views.
* Stream operator overloading.
* Compile-time and runtime validation.
* Clean separation between generation, verification, and presentation.
