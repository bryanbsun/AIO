# AIO 2019 — Teaching Notes
## Hiring Monks & Medusa's Snakes

---

# Problem 1: Hiring Monks

## Problem Summary

You have N monks (each with a skill level), S student jobs (each with a maximum skill cap), and M master jobs (each with a minimum skill requirement). Assign monks to jobs — one monk per job, one job per monk — to maximise total assignments.

- Student job j: monk skill **≤ $s_j$**
- Master job k: monk skill **≥ $m_k$**

---

## Step 1 — Understand the Structure

The first thing to notice: student jobs want **low-skill** monks, master jobs want **high-skill** monks. These are pulling in opposite directions. So sort everything.

If you draw monks on a number line by skill, student jobs "reach in from the left" and master jobs "reach in from the right."

---

## Step 2 — The Critical Insight (Exchange Argument)

**Claim:** There always exists an optimal solution where every monk assigned to a student job has skill ≤ every monk assigned to a master job.

**Proof:** Suppose monk A is in a student job and monk B is in a master job, but A's skill > B's skill. Then:
- B's skill ≤ A's skill ≤ student cap → B qualifies for the student job.
- A's skill ≥ B's skill ≥ master minimum → A qualifies for the master job.

So we can **swap** A and B without losing any assignment. Repeat swaps until all student-job monks have lower skill than all master-job monks.

**What this means:** In the optimal solution there is a "split point" in the sorted monk list. Monks below the split go to student jobs; monks above go to master jobs.

```
monks sorted: [low ... | ... high]
                         ^ split k
left side: compete for student jobs
right side: compete for master jobs
```

We try every possible split k (from 0 to N) and pick the best.

---

## Step 3 — Computing the Two Halves

Sort monks ascending, student caps ascending, master minimums ascending. Define:

- **f[k]** = max student matches using monks x[0..k-1] (the k lowest-skill monks)
- **g[k]** = max master matches using monks x[k..n-1] (the n-k highest-skill monks)

**Answer = max over k of (f[k] + g[k])**

### Computing f[] — Forward Greedy

For student jobs (cap ≥ monk's skill), process monks in ascending order. For each monk, assign it to the **smallest available cap that fits**. This is the greedy that maximises the number of student jobs filled.

Why is "smallest cap first" optimal? Because assigning a monk to the tightest-fitting cap leaves the looser caps available for higher-skill monks. Using a large cap for a low-skill monk would unnecessarily block higher-skill monks.

Two-pointer implementation:
```
j = 0 (pointer into sorted caps)
for k = 1 to n:
    skip caps too small: advance j while st[j] < x[k-1]
    if j < s:
        f[k] = f[k-1] + 1   (monk x[k-1] fills cap st[j])
        j++
    else:
        f[k] = f[k-1]        (no cap available)
```

**Why can we safely skip caps?** When we advance j past st[j] < x[k-1], that cap is too small for monk x[k-1] and also for all future monks (x[k], x[k+1], ..., which are even larger). So those caps can never be used again — it's safe to discard them.

> **DP Connection (for curious students):** f[k] = f[k-1] + (0 or 1). This IS a 1D dynamic programming recurrence! The "state" is how many monks we've considered so far, and the "value" is the maximum matches. The greedy just tells us efficiently whether monk k-1 adds a new match.

### Computing g[] — Backward Greedy

For master jobs (minimum ≤ monk's skill), we compute g from right to left — adding monks from the highest-skill downward.

For each new monk added (processed from x[n-1] down to x[0]), assign it to the **most demanding master job it can fill**. This leaves less-demanding jobs available for smaller monks added later.

Two-pointer (scanning jobs right to left):
```
j = m-1 (pointer into sorted master mins, starting at highest)
for k = n-1 down to 0:
    skip jobs too demanding: advance j left while ms[j] > x[k]
    if j >= 0:
        g[k] = g[k+1] + 1   (monk x[k] fills master job ms[j])
        j--
    else:
        g[k] = g[k+1]        (no suitable master job)
```

**Why is "most demanding first" optimal?** If monk x[k] fills a less-demanding job, the most-demanding job might go unfilled (no monk large enough remains). Filling the hardest possible job with the current monk leaves only easier jobs for smaller monks.

---

## Step 4 — Worked Example: The Bug in the Naive Greedy

A common first attempt: "assign master jobs first using the lowest-qualifying monk, then fill student jobs." **This is wrong.** Here's a counterexample:

```
Monks:         [5, 8, 12]
Student caps:  [9, 9]
Master mins:   [6]
```

**Naive greedy (wrong):**
- Master job (min 6): assign monk 8 (lowest ≥ 6). ✓ Count = 1.
- Student job (cap 9): highest unused monk ≤ 9 is monk 5. ✓ Count = 2.
- Student job (cap 9): no unused monks ≤ 9. Count stays 2.
- **Output: 2**

**Correct answer: 3**
- Monk 5 → student job (cap 9) ✓
- Monk 8 → student job (cap 9) ✓
- Monk 12 → master job (min 6) ✓

The naive greedy "wasted" monk 8 on the master job when monk 12 could fill it just as well, freeing monk 8 for a student job.

The split-point approach correctly tries k=2 (monks [5,8] for student jobs, monk [12] for master jobs), giving f[2]+g[2] = 2+1 = 3.

---

## Step 5 — Full Worked Trace (Sample 1)

```
Monks (sorted):  [20, 40, 100, 300, 1000]
Student caps:    [50, 110]
Master mins:     [300, 600, 2500]
```

**f[] computation:**
| k | monk added | cap pointer j | f[k] |
|---|-----------|---------------|------|
| 0 |     —     |       0       |  0   |
| 1 |    20     | st[0]=50 ≥ 20 → match, j→1 |  1   |
| 2 |    40     | st[1]=110 ≥ 40 → match, j→2 |  2   |
| 3 |   100     | j=2=s, no cap |  2   |
| 4 |   300     | j=2=s, no cap |  2   |
| 5 |  1000     | j=2=s, no cap |  2   |

**g[] computation (right to left):**
| k | monk x[k] | job pointer j | g[k] |
|---|-----------|---------------|------|
| 5 |     —     |       —       |  0   |
| 4 |   1000    | ms[2]=2500>1000→j--, ms[1]=600≤1000→match, j→0 |  1   |
| 3 |   300     | ms[0]=300≤300→match, j→-1 |  2   |
| 2 |   100     | j=-1 |  2   |
| 1 |    40     | j=-1 |  2   |
| 0 |    20     | j=-1 |  2   |

**f[k] + g[k]:**  0+2=2, 1+2=3, 2+2=**4**, 2+2=4, 2+1=3, 2+0=2

**Answer = 4** ✓ (best split at k=2: monks 20,40 → student; monks 100,300,1000 → master)

---

## Complexity

- Sorting: O(N log N + S log S + M log M)
- f[] pass: O(N + S)
- g[] pass: O(N + M)
- Final pass: O(N)
- **Total: O((N+S+M) log(N+S+M))**

For N, S, M ≤ 100,000 this is comfortably fast.

---

## Common Mistakes

1. **Doing master jobs first, then student jobs** — the order can matter, and this naive greedy is incorrect (see counterexample above).

2. **Not sorting** — the greedy only works when both monks and jobs are sorted.

3. **Forgetting the split-point idea** — without it, you might try to handle all jobs simultaneously, which is much harder.

4. **Reusing j for both passes** — f and g need separate pointers. Keep them independent.

---

---

# Problem 2: Medusa's Snakes

## Problem Summary

A snake's DNA is a string over `{S, N, A, K, E}`. Venom level x means the DNA (after deleting some letters) is exactly x S's, then x N's, then x A's, then x K's, then x E's (`S^x N^x A^x K^x E^x`). Find the maximum venom level achievable.

---

## Step 1 — Recognise the Pattern

We need to find the largest x such that "S^x N^x A^x K^x E^x" appears as a **subsequence** of the DNA. (Deleting letters from a string is the same as finding a subsequence.)

The answer x lies somewhere between 0 and N/5 (since 5x ≤ N).

---

## Step 2 — Binary Search on the Answer

**Can we achieve level x?** This is a Yes/No question. Crucially:

> If level x is achievable, then level x-1 is also achievable.

Why? If there are x S's before x N's before ... in order, we can just ignore the last S, last N, etc. and get x-1 of each.

This **monotonicity** means: achievable levels form a contiguous range [0, answer]. So we can **binary search** on x.

```
lo = 0, hi = N/5
while lo <= hi:
    mid = (lo + hi) / 2
    if check(mid): lo = mid + 1    ← can achieve mid, try higher
    else:          hi = mid - 1    ← cannot achieve mid, try lower
answer = hi
```

---

## Step 3 — Checking if Level x is Achievable

`check(x)`: scan the string once, greedily collecting x S's, then x N's, then x A's, then x K's, then x E's.

```cpp
bool check(int x) {
    int phase = 0, count = 0;
    for each character c in DNA:
        if c == letters[phase]:
            count++
            if count == x:
                count = 0; phase++
    return phase >= 5
}
```

**Why is greedy correct?** When collecting x S's (phase 0), take each S as early as possible. Delaying an S can only make things worse — the letters after any skipped S are the same, so there's nothing to gain. The same argument applies to each subsequent phase. Taking letters greedily (earliest available) never blocks a valid solution.

**Worked example — Sample 1:** `KSEESNANNAAKNKESE`, check(2)

| Position | Char | Phase | Count | Action |
|----------|------|-------|-------|--------|
| 0 | K | S | 0 | skip |
| 1 | S | S | 1 | collect |
| 2 | E | S | 1 | skip |
| 3 | E | S | 1 | skip |
| 4 | S | S | 2 | collect → phase→N |
| 5 | N | N | 1 | collect |
| 6 | A | N | 1 | skip |
| 7 | N | N | 2 | collect → phase→A |
| 8 | N | A | 0 | skip |
| 9 | A | A | 1 | collect |
| 10 | A | A | 2 | collect → phase→K |
| 11 | K | K | 1 | collect |
| 12 | N | K | 1 | skip |
| 13 | K | K | 2 | collect → phase→E |
| 14 | E | E | 1 | collect |
| 15 | S | E | 1 | skip |
| 16 | E | E | 2 | collect → phase→done |

phase = 5 ≥ 5 → `true`. Level 2 achievable ✓.

check(3) needs 3 S's. After collecting the 3rd S (position 15), no letters remain to collect 3 N's. Returns false. So level 3 not achievable, answer = 2. ✓

---

## Step 4 — Binary Search Trace (Sample 2)

`SSSSNNNAAAAKKKKEEEEEEE`, N=22.

lo=0, hi=4.
- mid=2: check(2) → trivially true (4 of each letter, all in order). lo=3.
- mid=3: check(3) → 4 S's exist → take first 3. 4 N's → take first 3. 4 A's → take 3. 4 K's → take 3. 7 E's → take 3. True. lo=4.
- mid=4: check(4) → 4 S's (just enough), 3 N's left after... 4 N's exist → take 4. 4 A's → take 4. 4 K's → take 4. 7 E's → take 4. True. lo=5.
- lo > hi=4. Answer = hi = 4?

Wait, hi=4 but expected answer is 3. Let me recheck.

Actually N/5 = 22/5 = 4. check(4): needs 4 S's. String has exactly 4 S's → takes all 4. Then needs 4 N's. String has 3 N's. Can only get 3 N's. Returns false. So:

- mid=4: false → hi=3.
- mid=3: true → lo=4.
- lo > hi → answer = hi = 3. ✓

---

## Complexity

- Binary search: O(log(N/5)) = O(log N) iterations
- Each `check`: O(N) scan
- **Total: O(N log N)**

For N ≤ 100,000, this is very fast.

---

## Common Mistakes

1. **Not recognising binary search applies** — students might try all x from 0 upward (O(N²) total) or only check x = min count of each letter (ignoring letter order).

2. **Wrong upper bound** — using `hi = N` instead of `N/5`. Minor issue (binary search still works, just slower).

3. **Incorrect check function** — e.g., resetting phase but not count, or checking the wrong letter.

4. **Forgetting x=0 is always achievable** — the binary search and check function must handle x=0 (empty subsequence). Important for strings where no valid subsequence exists.

---

## Connection to DP (for Students Interested in Dynamic Programming)

The greedy check can be viewed as a simple DP:

Define `dp[phase]` = how many letters of the current phase we've collected. We update this as we scan the string. But since each phase only starts after the previous completes, and we just track a counter, the "DP table" collapses to two variables (`phase` and `count`). This is a 1D DP optimised to O(1) space!

A more general DP approach (without binary search): let `dp[i]` = the largest x such that, reading only the first i characters of the DNA, we can form `S^x N^x A^x K^x E^x` as a subsequence. This leads to O(N²) time. The binary search + greedy approach improves this to O(N log N) by exploiting the monotonicity.

This is a common pattern in competitive programming: **binary search on the answer + greedy/DP feasibility check**. When you see a problem asking for "the maximum value of x such that something works," immediately ask: "Is this monotone in x? Can I check feasibility quickly?"

---

## Connection to DP (for Students Interested in Dynamic Programming)

**Hiring Monks** also has a DP flavour. The f[] array satisfies:
```
f[0] = 0
f[k] = f[k-1]     (monk x[k-1] gets no student job)
     or f[k-1]+1  (monk x[k-1] gets a student job)
```
This is a 1D DP where each state only depends on the previous state. The greedy two-pointer tells us in O(1) which case applies.

Similarly g[] is a 1D DP computed from right to left.

These are your first taste of DP: the key principle is **optimal substructure** — the best solution for monks[0..k] can be built from the best solution for monks[0..k-1] plus a decision about monk k. We don't need to remember the full assignment, just the count. That's the power of DP.

---

## Summary Table

| Problem | Core Technique | Key Insight |
|---------|---------------|-------------|
| Hiring Monks | Greedy + Two Pointers | Exchange argument → split point → independent f[] and g[] passes |
| Medusa's Snakes | Binary Search on Answer + Greedy Check | Achievability is monotone → binary search; greedy left-to-right scan for check |

Both problems reward asking: *"Can I sort the input and process it in order?"* and *"Is there a simpler structure hiding in the optimal solution?"*
