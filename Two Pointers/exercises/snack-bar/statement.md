# Exercise 2 — Snack Bar

**Technique:** variable-size sliding window (two pointers).

## Story

A snack bar lays out `N` items in a single row. Item `i` costs `p[i]` dollars.
You have a budget of `B` dollars and a rule you've set yourself: you'll only buy
a **contiguous** run of items (no skipping). Buy the **longest** run of
consecutive items whose total cost does **not** exceed `B`.

Report how many items are in that longest affordable run. If even a single item
is too expensive to buy, the answer is `0`.

## Input

- Line 1: an integer `N` and an integer `B`  (`1 ≤ N ≤ 100000`, `0 ≤ B ≤ 10^18`).
- Line 2: `N` integers `p[1] … p[N]`  (`1 ≤ p[i] ≤ 1000000000`).

## Output

A single integer: the maximum number of consecutive items whose total cost is
`≤ B`.

> Note: a running total of prices can exceed 32-bit range — use 64-bit
> (`long long`).

## Sample

**Input**
```
7 10
3 1 4 1 5 9 2
```

**Output**
```
4
```

**Explanation.** The run `3 1 4 1` costs `9 ≤ 10` and has length `4`. No run of
length `5` costs `≤ 10` (for example `3 1 4 1 5 = 14`), so the answer is `4`.

## Why two pointers works here

All prices are **positive**, so as the left end of the window moves right, the
total only goes down — meaning the furthest affordable right end never moves
backward. That monotonicity is exactly what lets both pointers sweep forward once
each, giving `O(N)`.

## Target complexity

`O(N)`. Expand the right pointer to add an item; whenever the total exceeds `B`,
advance the left pointer (subtracting items) until it fits again; track the best
length seen. Each pointer moves at most `N` steps in total.

## Tests

Ten cases are provided in `tests/` as `NN.in` / `NN.out`. They cover: the sample,
a single affordable item, a single unaffordable item, every item too expensive
(answer `0`), a budget large enough for all items (answer `N`), an exact-fit
boundary, a case whose prefix sums overflow 32-bit integers, the best run sitting
in the middle, and a large `N = 100000` case to confirm your solution is linear
(the `O(N^2)` brute force times out here).
