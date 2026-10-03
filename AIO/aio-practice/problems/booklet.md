# AIO-Style Practice Contest — 2026 Set

**Duration: 3 hours · 6 problems · 100 points each (600 total) · increasing difficulty**

Modelled on the Australian Informatics Olympiad (2022–2025 style): six
scenario-based problems of increasing difficulty, each worth 100 points split
across subtasks. Submit a program that reads from standard input and writes to
standard output. A subtask scores full marks only if every one of its test
cases passes within the time and memory limits (partial-credit subtasks reward
slower solutions on small inputs). Allowed leniency: leading/trailing whitespace
on each line is ignored.

| # | Problem | Core skill | Difficulty |
|---|---------|-----------|-----------|
| 1 | Rover | simulation | easy |
| 2 | Rainfall | prefix sums | easy |
| 3 | Concerts | greedy | medium |
| 4 | Training | two pointers / sliding window | medium |
| 5 | Shipping | binary search on answer + greedy | hard |
| 6 | Twin Peaks | prefix sums + linear sweep (capstone) | hard |

---

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

---

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

---

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

---

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

---

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

---

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

---

