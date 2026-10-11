# Problem 2 — Rainfall  (100 points)

**Skill: prefix sums**  ·  Time limit: 4.0 s  ·  Memory limit: 256 MB

A weather station recorded the rainfall for each of `N` days. You are given
`Q` questions from researchers. Each question gives two days `l` and `r`
(`l ≤ r`) and asks for the **total rainfall** on days `l` through `r`
inclusive.

## Input
- Line 1: integers `N` and `Q`.
- Line 2: `N` integers `r_1 … r_N` — the rainfall on each day.
- Next `Q` lines: two integers `l` and `r` (1-indexed).

## Output
`Q` lines: the answer to each question, in order.

## Constraints
- `1 ≤ N, Q ≤ 200000`
- `0 ≤ r_i ≤ 10^9`
- `1 ≤ l ≤ r ≤ N`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 30 | `N, Q ≤ 2000` |
| 2 | 30 | `N, Q ≤ 200000`, `r_i ≤ 1000` |
| 3 | 40 | no extra constraints |

## Sample input
```
5 3
2 4 1 3 5
1 3
2 5
4 4
```
## Sample output
```
7
13
3
```
### Explanation
Days 1–3: `2+4+1 = 7`. Days 2–5: `4+1+3+5 = 13`. Day 4 only: `3`.

> **Hint.** Answering each query by looping is `O(N)` per query — too slow when
> both `N` and `Q` are large. Pre-compute prefix sums `P[k] = r_1+…+r_k` once in
> `O(N)`; then every query is `P[r] − P[l−1]` in `O(1)`. A full-range total can
> reach `2×10^14`, so use 64-bit integers for the prefix sums.
