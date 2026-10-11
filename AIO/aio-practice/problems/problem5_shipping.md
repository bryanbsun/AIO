# Problem 5 — Shipping  (100 points)

**Skill: binary search on the answer + greedy**  ·  Time limit: 4.0 s  ·  Memory limit: 256 MB

A conveyor delivers `N` packages in a fixed order; package `i` weighs `w_i`.
They must all be shipped within `D` days. Each day a single ship departs
carrying a **contiguous** group of the packages that are next in line (you may
not reorder them). Every package must be shipped, and each of the `D` days must
be used for at least one package — in other words, you split the sequence into
`D` contiguous non-empty groups, in order, one per day.

A ship has a fixed weight capacity `C` and can carry a day's group only if the
group's total weight is at most `C`. Find the **minimum** capacity `C` for which
a valid shipping schedule exists.

(Equivalently: split the sequence into `D` contiguous parts so that the largest
part-sum is as small as possible, and report that largest part-sum.)

## Input
- Line 1: integers `N` and `D`.
- Line 2: `N` integers `w_1 … w_N`.

## Output
A single integer: the minimum ship capacity `C`.

## Constraints
- `1 ≤ D ≤ N ≤ 200000`
- `1 ≤ w_i ≤ 10^9`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 20 | `N ≤ 20` |
| 2 | 30 | `N ≤ 2000` |
| 3 | 50 | no extra constraints |

## Sample input
```
5 2
3 6 7 11 5
```
## Sample output
```
16
```
### Explanation
Split as `[3,6,7]` (sum 16) and `[11,5]` (sum 16). The larger group is `16`, and
no split into 2 groups does better, so the minimum capacity is `16`.

> **Hint.** The answer lies between `max(w_i)` and `sum(w_i)`. Binary search on
> the capacity `C`. To test a capacity, greedily fill each ship until the next
> package would overflow, then start a new day, and count the days used; `C`
> works if that count is `≤ D`. The feasibility check is `O(N)`, so the whole
> solution is `O(N log(sum))`. Use 64-bit integers for the sums.
