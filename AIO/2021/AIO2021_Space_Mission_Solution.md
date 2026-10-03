# AIO 2021 — Problem 5: Space Mission
## Full Analysis, Solution, and Teaching Notes

---

## 1. Restating the Problem in Algorithmic Terms

Strip away the story and the problem becomes:

> You are given an array `C[1..N]` of positive integers and a budget `F`.
> Choose two **distinct** indices `L` and `R` with `L < R` such that
> `C[L] + C[R] <= F`, maximizing `R - L + 1`.
> If no such pair exists, output `-1`.

Why `R - L + 1`? The probe collects one sample on every day from the launch
day to the return day **inclusive**, so the number of samples is simply the
number of days spanned by the interval `[L, R]`.

Why `L < R` and not just `L != R`? The launch must happen before the return
in time, so we may assume WLOG that `L` is the earlier day and `R` the later
day — order doesn't change the answer, it just simplifies bookkeeping.

This reformulation is the single most important step: once you see it as
"maximize index distance subject to a sum constraint," the combinatorics of
gas, portals, and supernovas disappear and you're left with a clean
two-array problem.

---

## 2. Why the Obvious Approaches Aren't Enough

### Brute force — O(N²)
Try every pair `(L, R)`, check `C[L] + C[R] <= F`, track the best
`R - L + 1`. This is **correct** and is exactly what Subtask 1 (`N ≤ 1000`)
rewards — with `N` up to 1000, 10⁶ pair-checks run instantly.

```python
best = -1
for L in range(N):
    for R in range(L + 1, N):
        if C[L] + C[R] <= F:
            best = max(best, R - L + 1)
```

This is a good first submission: it's quick to write, easy to get right
under contest pressure, and locks in partial credit. **Always bank the easy
subtask before chasing the full solution.**

For `N = 100000`, however, `N²` is `10^10` operations — far too slow for a
1-second limit. We need something close to `O(N log N)`.

### "Sort by cost?" — a tempting but broken idea
A natural instinct is to sort indices by `C[i]` and use a two-pointer sweep
(like the classic "two-sum" problem). The trouble is that sorting by cost
**destroys the index information** that the objective function actually
depends on. Two-sum/two-pointer works when you're optimizing something about
the *values*; here we're optimizing something about the *positions*, while
the *values* only gate which positions are allowed to pair up. This mismatch
is exactly why this problem is more subtle than it first looks, and it's a
great discussion point for students: **identify what you're optimizing
versus what you're filtering on — sorting by the wrong key throws away the
thing you actually need.**

---

## 3. The Key Insight: Prefix Minima Are the Only Candidates That Matter

Fix a return day `j`. We want the **smallest possible index `i < j`** with
`C[i] <= F - C[j]`, because making the interval start as early as possible
maximizes `j - i + 1`.

Now ask: among all indices `i < j`, which ones could *ever* be the best
choice for *some* threshold? Suppose index `i'` comes before index `i`
(`i' < i`) and `C[i'] <= C[i]`. Then `i'` is **strictly better than or equal
to** `i` in every respect — it's both earlier *and* at least as cheap. So
`i` is never going to be chosen over `i'`; it is **dominated** and can be
discarded forever.

The indices that survive this domination test are exactly the **prefix
minima** of `C`: the sequence of indices `i_1 < i_2 < ... < i_k` where each
$i_m$ sets a new record low cost, i.e. $C[i_1] > C[i_2] > \ldots > C[i_k]$
(strictly decreasing costs, as you scan left to right).

This list has two beautiful properties:
1. It is the **complete set of candidates** we will ever need to consider as
   a launch day.
2. Because costs strictly **decrease** as index **increases** along the
   list, for any threshold `T` the set of entries satisfying `C[i] <= T`
   forms a contiguous **suffix** of the list. That means we can binary
   search it.

### The algorithm
Sweep `j` from day 1 to day N, maintaining the prefix-minima list of
`C[1..j-1]` (i.e., everything strictly before `j`):

1. Compute the threshold `T = F - C[j]`.
2. Binary search the prefix-minima list for the **leftmost** entry with
   `C[i] <= T`. (Leftmost = smallest index = best candidate, by the
   monotonic-suffix property above.)
3. If found, the candidate answer is `j - i + 1`.
4. Append `j` to the prefix-minima list **if and only if** `C[j]` is smaller
   than the current minimum (i.e., it's a new record low) — otherwise it's
   dominated by something already in the list and can be safely ignored.
5. After processing all `j`, the largest candidate answer found is the
   answer; if none was ever found, output `-1`.

Because each index is pushed onto the list at most once, and each query is
a binary search over a list of size at most `N`, the whole algorithm runs
in **O(N log N)** time and **O(N)** space.

---

## 4. Worked Trace (Sample Input 2)

`C = [12, 8, 2, 16, 4, 6, 10]`, `F = 14`. Prefix-minima list shown as
`(index, cost)` pairs, kept in increasing index / decreasing cost order.

| j | C[j] | Threshold T = F−C[j] | List before query | Search result | Candidate (j−i+1) | List after update |
|---|------|----|--------------------------|----------------|----|--------------------------|
| 1 | 12 | 2  | [ ]                       | none           | —  | [(1,12)] |
| 2 | 8  | 6  | [(1,12)]                  | none (12 > 6)  | —  | [(1,12),(2,8)] |
| 3 | 2  | 12 | [(1,12),(2,8)]            | i=1 (12 ≤ 12)  | 3  | [(1,12),(2,8),(3,2)] |
| 4 | 16 | −2 | [(1,12),(2,8),(3,2)]      | none (T<0)     | —  | unchanged |
| 5 | 4  | 10 | [(1,12),(2,8),(3,2)]      | i=2 (8 ≤ 10)   | 4  | unchanged (4 > 2) |
| 6 | 6  | 8  | [(1,12),(2,8),(3,2)]      | i=2 (8 ≤ 8)    | **5**  | unchanged (6 > 2) |
| 7 | 10 | 4  | [(1,12),(2,8),(3,2)]      | i=3 (2 ≤ 4)    | 5  | unchanged |

Best candidate = **5**, matching the expected output (launch day 2, return
day 6: `8 + 6 = 14 ≤ F`, spanning 5 days).

---

## 5. Reference Implementations

Both versions binary-search a Python `list` / C++ `vector` of
`(cost, index)` prefix minima. Costs are kept **descending**, so a standard
binary search for "first element ≤ T" applies directly.

### Python

```python
import sys
from bisect import bisect_left

def solve():
    data = sys.stdin.read().split()
    idx = 0
    N, F = int(data[idx]), int(data[idx + 1]); idx += 2
    C = [int(data[idx + i]) for i in range(N)]; idx += N

    # prefix_costs is stored in DECREASING order, so we negate to use
    # bisect_left (which expects ascending order) on the negated values.
    prefix_costs_neg = []   # -C[i], decreasing C  ==>  increasing -C
    prefix_idx = []         # corresponding 1-based day index
    best = -1

    for j in range(1, N + 1):
        cj = C[j - 1]
        T = F - cj
        if prefix_costs_neg:
            # find leftmost position with cost <= T  <=>  -cost >= -T
            # i.e. first position where (-cost) >= -T
            pos = bisect_left(prefix_costs_neg, -T)
            if pos < len(prefix_costs_neg):
                i = prefix_idx[pos]
                best = max(best, j - i + 1)
        # update prefix minima
        if not prefix_costs_neg or cj < -prefix_costs_neg[-1]:
            prefix_costs_neg.append(-cj)
            prefix_idx.append(j)

    print(best)

solve()
```

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    long long F;
    scanf("%d %lld", &N, &F);

    vector<long long> C(N + 1);
    for (int i = 1; i <= N; i++) scanf("%lld", &C[i]);

    // prefix minima, stored with DECREASING cost as index increases
    vector<long long> costs;   // decreasing
    vector<int> idxs;          // increasing day index
    long long best = -1;

    for (int j = 1; j <= N; j++) {
        long long T = F - C[j];
        if (!costs.empty()) {
            // find leftmost position with costs[pos] <= T
            // costs is decreasing -> use a custom binary search
            int lo = 0, hi = (int)costs.size(); // hi = "not found"
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (costs[mid] <= T) hi = mid;
                else lo = mid + 1;
            }
            if (lo < (int)costs.size()) {
                best = max(best, (long long)(j - idxs[lo] + 1));
            }
        }
        if (costs.empty() || C[j] < costs.back()) {
            costs.push_back(C[j]);
            idxs.push_back(j);
        }
    }

    printf("%lld\n", best);
    return 0;
}
```

Both implementations have been traced against all three sample inputs and
reproduce outputs `4`, `5`, and `-1` respectively.

---

## 6. Complexity

- **Time:** O(N log N) — one binary search per day, each O(log N).
- **Space:** O(N) — the prefix-minima list never exceeds N entries.

This comfortably fits a 1-second limit for `N ≤ 100000`.

---

## 7. Common Pitfalls (worth flagging to students explicitly)

1. **Integer overflow.** `F` and `C[i]` can each be up to `10^9`; their sum
   can reach `2 × 10^9`, which overflows a 32-bit signed integer
   (max ≈ 2.147 × 10^9 — *technically* still fits, but `F - C[j]` and other
   intermediate sums in related problems often don't). The safe habit is
   to use `long long` in C++ (or just trust Python's arbitrary precision)
   for any sum involving `F` or `C`.
2. **Off-by-one on the sample count.** It's `R - L + 1`, not `R - L` — the
   launch and return days both count as collection days.
3. **Forgetting `L ≠ R`.** A single day can never be both launch and
   return, so an index can't pair with itself. The prefix-minima sweep
   naturally respects this since we only ever search the list *before*
   appending `j`.
4. **Negative or zero thresholds.** When `F - C[j] < 1`, no valid launch
   day exists for that particular return day (since all costs are
   ≥ 1) — the binary search will correctly report "not found" as long as
   you don't special-case it incorrectly. No extra logic is needed beyond
   handling "binary search found nothing."
5. **Confusing "smallest cost" with "smallest index."** This is the crux
   trap of the whole problem. The greedy candidate set is prefix minima
   *by cost*, but what we ultimately search for is the *smallest index*
   meeting a cost threshold — these are related but distinct ideas, and
   conflating them leads to incorrect pruning logic.

---

## 8. Subtask-by-Subtask Strategy (useful for partial-credit thinking)

| Subtask | Constraint | Suggested approach |
|---|---|---|
| 1 (20 pts) | `N ≤ 1000` | Brute-force O(N²) over all pairs. |
| 2 (50 pts) | `F ≤ 100` | **Bucket trick**: since any useful cost must be `≤ F ≤ 100`, maintain an array `best[0..F]` where `best[t]` = smallest index seen so far with `C[i] ≤ t`. This is a simple running "minimum prefix" update in O(F) per step, giving O(N·F) ≈ O(N·100) total — well within limits, and conceptually simpler than binary search for students still building intuition. |
| 3 (30 pts) | full constraints | The O(N log N) prefix-minima + binary search solution above. |

The bucket-trick for Subtask 2 is worth teaching on its own: it's the same
"keep only the best candidate for each threshold" idea as the full
solution, just indexed directly by cost instead of binary-searched. Seeing
both versions back-to-back helps students notice that **the full solution
is really just replacing an O(F)-sized array with an O(log N) binary
search over a compressed list of "interesting" thresholds** — a pattern
that recurs constantly in competitive programming (offline queries +
some form of compressed/sparse index).

---

## 9. Extension Questions for Practice

These are good for follow-up discussion or as bonus exercises:

1. **What if you could use more than one round trip** (i.e., pick `k`
   disjoint launch/return pairs, total fuel ≤ F, maximize total samples
   collected, with no day counted twice if intervals overlap)? How does
   the structure of the problem change?
2. **What if fuel cost depended on the gap** between launch and return
   (e.g., `cost = C[L] + C[R] + (R - L)`)? Does the prefix-minima trick
   still apply, and if not, what would you need to change?
3. Can you solve the original problem **online** (i.e., answer "what's the
   best pair using only days seen so far" after each new day arrives,
   without knowing N in advance)? Check that the algorithm above already
   has this property — it's a nice thing to point out explicitly, since it
   shows the technique is more general than the offline problem demands.
4. Prove rigorously that discarding non-prefix-minima indices never
   discards an optimal answer. (This is the domination argument in
   Section 3 — turning the intuition into a clean two-line proof is good
   practice for written solutions/proof-based rounds.)

---

## 10. One-Paragraph Summary (for quick review before a contest)

*Space Mission* reduces to: maximize `R - L + 1` over `L < R` with
`C[L] + C[R] ≤ F`. The brute-force O(N²) scan over all pairs earns partial
credit. The full solution recognizes that, for a fixed `R`, only indices
that are **prefix minima of cost** can ever be the optimal `L` — all other
indices are dominated by an earlier, cheaper index. Because prefix minima
have strictly decreasing cost as index increases, a binary search finds the
best `L` for any given cost threshold in O(log N), giving an overall
O(N log N) solution. The general lesson — discard dominated candidates,
keep only a monotonic "frontier," and binary search the frontier — is a
recurring competitive programming pattern well beyond this one problem.
