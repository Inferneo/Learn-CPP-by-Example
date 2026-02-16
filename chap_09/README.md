# Triangle Slot Machine (C++20)

A small C++20 console slot machine built on triangle numbers.

Each reel contains the first *n* triangle numbers, shuffled independently.
On every round you can:

* **H**old a reel
* **N**udge it by one position
* **S**pin it randomly
* Press **Enter** to spin all

The visible result is the first element of each reel. Payout is determined by the **last digit** of each visible number:

* Three matching digits pay more than two.
* Digits **3** and **8** are high-value symbols.

The project also demonstrates:

* `std::ranges`
* `std::views::zip`
* `std::variant` + `std::visit`
* Fold expressions
* Concepts
* `<execution>` parallel algorithms
* `<format>`
* Modern random facilities (`std::mt19937`)
* Compile-time and runtime `std::optional`

## Build

Requires a C++20-compliant compiler.

```bash
g++ -std=c++20 -O2 main.cpp -o triangle_machine
```

## Run

```bash
./triangle_machine
```

Press Enter to play.
Type `h`, `n`, or `s` per reel when prompted.
