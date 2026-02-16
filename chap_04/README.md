# Chrono Countdown Demo (C++20/23)

A small C++ program demonstrating modern `<chrono>` features, including:

* `year_month_day`, `sys_days`, and calendrical arithmetic
* `duration` conversions and custom duration types
* `constexpr` time computations with `static_assert`
* Time zone–aware calculations with `zoned_time`
* Parsing dates using `std::chrono::parse`
* Concepts (`Quacks`) and constrained templates

## Features

* Compute days until an arbitrary date (`YYYY-MM-DD`)
* Countdown to New Year’s Eve
* Example of “last Friday of the month” calculation
* Custom duration type (`centuries`)
* Compile-time validation of time logic
* Optional-based date parsing with error handling

## Requirements

* C++20 or later (C++23 recommended for full `<chrono>` support)
* Standard library with time zone database support (for `zoned_time`)

Example compiler:

```bash
g++ -std=c++23 -O2 main.cpp -o countdown
```

## Usage

Run the program and enter a date in ISO format:

```
2026-12-31
```

Output:

```
X days until 2026-12-31
```

## Notes

* Date input must follow `YYYY-MM-DD`.
* Time zone functionality depends on your standard library implementation.
* Some features (e.g., time zones) may require linking against the system time zone database.
