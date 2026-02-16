# Smash

Smash is a small C++ word game that combines two overlapping words into a single “smash” word. Given a first word and a dictionary, the program finds a second word whose prefix matches a suffix of the first word, then prompts the user to guess the combined result.

## How It Works

1. Select a keyword (e.g., from `keywords.csv`).
2. Search the dictionary for a word whose prefix matches a suffix of the keyword.
3. Display both definitions.
4. The user enters the combined word:

   ```
   first_word_prefix + second_word
   ```

Example logic:

* Word: `class`
* Overlap: `ass`
* Dictionary word: `assume`
* Result: `classume`

## Features

* Loads keywords and dictionary entries from CSV files.
* Case-insensitive input handling.
* Random sampling of words using `std::mt19937`.
* Uses `std::multimap` to support multiple definitions per word.
* Generic selection strategy via templated overlap selection.

## Build

Requires a C++20-compatible compiler.

Example (GCC/Clang):

```bash
g++ -std=c++20 -O2 main.cpp Smash.cpp -o smash
```

Ensure `dictionary.csv` and `keywords.csv` are present in the working directory.

## Files

* `Smash.h` – Declarations and templated overlap logic.
* `Smash.cpp` – Implementation.
* `main.cpp` – Entry point.
* `dictionary.csv` – Word, definition pairs.
* `keywords.csv` – Keyword, definition pairs.

## Notes

* Overlap detection scans increasing suffix offsets.
* Dictionary lookup uses lexicographic bounds (`lower_bound` / `upper_bound`) to find prefix matches efficiently.
* Random selection is performed with `std::ranges::sample` and `std::sample`.
