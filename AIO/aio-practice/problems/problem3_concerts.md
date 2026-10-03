# Problem 3 — Concerts  (100 points)

**Skill: greedy**  ·  Time limit: 4.0 s  ·  Memory limit: 256 MB

There are `N` concerts today. Concert `i` starts at time `s_i` and finishes at
time `e_i`. You would like to attend as many concerts as possible, but you can
only be at one concert at a time. Two concerts clash if their time intervals
overlap; however, if one concert finishes at *exactly* the moment another
starts (`e_i = s_j`) you can dash between them, so that is allowed.

Find the maximum number of concerts you can attend.

## Input
- Line 1: integer `N`.
- Next `N` lines: two integers `s_i` and `e_i` (`s_i < e_i`).

## Output
A single integer: the maximum number of non-overlapping concerts.

## Constraints
- `1 ≤ N ≤ 200000`
- `0 ≤ s_i < e_i ≤ 10^9`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 20 | `N ≤ 20` |
| 2 | 30 | `N ≤ 2000` |
| 3 | 50 | no extra constraints |

## Sample input
```
4
1 3
2 5
4 6
6 7
```
## Sample output
```
3
```
### Explanation
Attend `[1,3]`, then `[4,6]`, then `[6,7]` (the last two touch at time 6,
which is allowed). Concert `[2,5]` clashes with `[1,3]`, so it is skipped.
Three concerts is the best possible.

> **Hint.** Sort the concerts by **finishing time**. Repeatedly attend the
> concert that finishes earliest among those that don't clash with the last one
> you chose. Greedily finishing early leaves the most room for later concerts.
> Sorting makes this `O(N log N)`.
