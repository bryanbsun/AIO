# Exercise 1 — Assembly Line

**Technique:** fixed-size sliding window.

## Story

A factory assembly line has `N` stations in a row. Station `i` produced `d[i]`
defective parts during the last shift. The quality manager will shut down a run
of exactly `K` **consecutive** stations for maintenance and wants to disrupt as
little quality as possible — so she picks the `K` consecutive stations whose
total defect count is **smallest**.

Report that smallest total.

## Input

- Line 1: two integers `N` and `K`  (`1 ≤ K ≤ N ≤ 100000`).
- Line 2: `N` integers `d[1] … d[N]`  (`0 ≤ d[i] ≤ 1000000000`).

## Output

A single integer: the minimum possible total number of defects over any block of
`K` consecutive stations.

> Note: the total can exceed the range of a 32-bit integer — use 64-bit
> (`long long`).

## Sample

**Input**
```
6 3
7 2 5 1 4 6
```

**Output**
```
8
```

**Explanation.** The four blocks of 3 consecutive stations have totals
`7+2+5 = 14`, `2+5+1 = 8`, `5+1+4 = 10`, `1+4+6 = 11`. The smallest is `8`.

## Target complexity

`O(N)`. Build the first window in `O(K)`, then slide: on each step add the
entering station and subtract the leaving station in `O(1)`.

## Tests

Ten cases are provided in `tests/` as `NN.in` / `NN.out`. They cover: the sample,
a single station, `K = N` (whole line), `K = 1`, all-zero input, a minimum block
forced to the interior, a case that overflows 32-bit integers, and a large
`N = 100000` case to confirm your solution is linear (the `O(NK)` brute force
times out here).
