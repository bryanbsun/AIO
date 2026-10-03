# Problem 6 — Twin Peaks  (100 points)

**Skill: prefix sums + linear sweep (capstone)**  ·  Time limit: 4.0 s  ·  Memory limit: 256 MB

A tourist road has `N` towns in a row; town `i` earns you `a_i` dollars if you
run a stall there. You will open stalls in **two** separate stretches of road:
one stretch of exactly `L` consecutive towns and another of exactly `R`
consecutive towns. The two stretches must **not overlap** (they may touch at an
endpoint town only in the sense of being adjacent — no town is shared). Either
stretch may lie to the left of the other.

Maximise the total money earned from all `L + R` chosen towns.

## Input
- Line 1: integers `N`, `L`, `R`.
- Line 2: `N` integers `a_1 … a_N`.

## Output
A single integer: the maximum total earnings.

## Constraints
- `1 ≤ L, R` and `L + R ≤ N ≤ 200000`
- `0 ≤ a_i ≤ 10^9`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 20 | `N ≤ 400` |
| 2 | 30 | `N ≤ 5000` |
| 3 | 50 | no extra constraints |

## Sample input
```
6 1 2
4 1 3 2 5 1
```
## Sample output
```
11
```
### Explanation
Take the `R = 2` stretch `[2,5]` (towns 4–5, worth 7) and the `L = 1` stretch
`[4]` (town 1, worth 4). They don't overlap, for a total of `11`, which is the
best achievable.

> **Hint.** Build prefix sums so any window's total is `O(1)`. Consider the two
> orderings separately: the `L`-window entirely before the `R`-window, and vice
> versa. For one ordering, sweep the start of the second window from left to
> right while keeping the best first-window sum seen so far to its left (a
> running maximum over precomputed window sums). Combine the two orderings for
> the answer. Overall `O(N)`; use 64-bit integers.
