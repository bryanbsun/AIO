# Problem 4 — Training  (100 points)

**Skill: two pointers / sliding window**  ·  Time limit: 3.0 s  ·  Memory limit: 256 MB

An athlete has a training plan of `N` days. Day `i` requires effort `a_i`
(a positive number). To avoid burning out, the athlete will only train on a
**contiguous** block of days whose total effort is at most `K`.

What is the greatest number of consecutive days the athlete can train? If even
a single day exceeds `K`, the answer is `0`.

## Input
- Line 1: integers `N` and `K`.
- Line 2: `N` integers `a_1 … a_N`.

## Output
A single integer: the length of the longest contiguous block with total effort
`≤ K`.

## Constraints
- `1 ≤ N ≤ 200000`
- `1 ≤ a_i ≤ 10^9`
- `1 ≤ K ≤ 10^18`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 20 | `N ≤ 2000` |
| 2 | 30 | `N ≤ 200000`, `a_i ≤ 1000`, `K ≤ 10^9` |
| 3 | 50 | no extra constraints |

## Sample input
```
6 8
3 1 4 1 5 2
```
## Sample output
```
3
```
### Explanation
`[3,1,4]` sums to `8 ≤ 8` (length 3), as does `[1,5,2]`. No block of length 4
stays within `8` (e.g. `[3,1,4,1] = 9`). So the answer is `3`.

> **Hint.** Because every `a_i` is positive, use two pointers. Grow the window
> to the right one day at a time; whenever the running sum exceeds `K`, shrink
> it from the left. Each pointer only moves forward, giving `O(N)`. The running
> sum can reach `2×10^14`, so use 64-bit integers.
