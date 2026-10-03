# Problem 1 — Rover  (100 points)

**Skill: simulation**  ·  Time limit: 3.0 s  ·  Memory limit: 256 MB

A Mars rover starts at position `0` on an infinite number line. It then
receives `N` movement commands. The `i`-th command is an integer `m_i`
(never zero): the rover drives `m_i` metres, to the right if `m_i` is
positive and to the left if `m_i` is negative. The rover moves **smoothly**,
so it occupies every integer position it passes over on the way.

Mission control wants two numbers once all commands are done:

1. the number of **distinct integer positions** the rover has ever occupied
   (including its starting position `0`), and
2. the rover's **final position**.

## Input
- Line 1: integer `N`.
- Next `N` lines: one integer `m_i` per line.

## Output
One line with two integers separated by a space: the number of distinct
positions occupied, then the final position.

## Constraints
- `1 ≤ N ≤ 200000`
- `-10^9 ≤ m_i ≤ 10^9`, `m_i ≠ 0`

## Subtasks
| # | Points | Extra constraints |
|---|--------|-------------------|
| 1 | 30 | `N ≤ 1000`, `|m_i| ≤ 1000` |
| 2 | 30 | `N ≤ 200000`, `|m_i| ≤ 1000` |
| 3 | 40 | no extra constraints |

## Sample input
```
3
5
-8
2
```
## Sample output
```
9 -1
```
### Explanation
The rover goes `0 → 5` (covering 0..5), then `5 → -3` (covering -3..5), then
`-3 → -1`. The furthest right it reached is `5`, the furthest left is `-3`, so
it has covered every integer from `-3` to `5`: that is `5-(-3)+1 = 9` distinct
positions. Its final position is `-1`.

> **Hint.** You never need to store every position. The set of positions
> visited is exactly the range between the smallest and largest position the
> rover was ever *at*. Track a running position together with its running
> minimum and maximum. Note that the final position can be as large as
> `2×10^14`, so 32-bit integers overflow — use 64-bit (`long long` in C++,
> `long` in Java; Python is fine).
