# AIO Contest Cheat Sheet

*Prefix Sums · Two Pointers · Binary Search & Binary Answers · Greedy — one page per topic. Print it, bring it, use it.*

> **How to use in-contest:** read the **Signal** box first — it tells you *when* a problem is asking for this technique. Then copy the template, adapt the "summary" you maintain, and check the **Traps** before you submit. Every snippet uses only `<iostream>` (Greedy also uses `<algorithm>` for `sort`) and compiles as-is.

---

## PAGE 1 — Prefix Sums

**Idea:** pay `O(N)` once to precompute cumulative sums, then answer *any* range-sum query in `O(1)` with one subtraction.

### Signal — reach for this when you see…
- "sum / count / total of a **range** `[l, r]`", asked **many times**, or over **many candidate ranges**.
- a fixed array that **does not change**, but ranges you query repeatedly.
- a grid with repeated **sub-rectangle** sum/count queries → 2D version.
- "**apply many range add operations**, then read the array once" → difference array (the inverse).

### 1D prefix sum — the core
Use **1-indexed** arrays and the sentinel `s[0] = 0`; it kills most off-by-one bugs.

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long a[MAXN], s[MAXN];   // ALWAYS long long: sums overflow int

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    s[0] = 0;                                    // sentinel
    for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];   // O(n) precompute

    while (q--) {                                // each query O(1)
        int l, r; cin >> l >> r;
        cout << s[r] - s[l-1] << "\n";           // sum of a[l..r]
    }
    return 0;
}
```

**Key identity:** `sum(l, r) = s[r] - s[l-1]`. Any range = difference of two prefixes.

### Fixed-length window sum (e.g. best K consecutive)
Right endpoint `i` covers `a[i-K+1 .. i]`, whose sum is `s[i] - s[i-K]`:

```cpp
long long best = -1;
for (int i = k; i <= n; i++) {                   // i = window's right end
    long long win = s[i] - s[i-k];
    if (best == -1 || win > best) best = win;
}
```
Turns the naive `O(N·K)` scan into `O(N)`.

### 2D prefix sum — sub-rectangle sums
Build with inclusion–exclusion; 1-indexing makes row/col 0 all zero automatically.

```cpp
for (int i = 1; i <= n; i++)
  for (int j = 1; j <= m; j++)
    s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];

// rectangle with corners (r1,c1) top-left, (r2,c2) bottom-right:
long long sum = s[r2][c2] - s[r1-1][c2] - s[r2][c1-1] + s[r1-1][c1-1];
```

### Difference array — the inverse (many range-adds, read once)
For each "add `v` to `[l, r]`": `diff[l] += v; diff[r+1] -= v;`  Then a prefix sum of `diff` gives the final array. Each update `O(1)`, final rebuild `O(n)`.

### Reversible vs not — a rule that saves you
- **sum, XOR** are **reversible** → prefix array answers **any** range.
- **max, min, gcd** have **no inverse** → prefix/suffix arrays only answer ranges with a **fixed endpoint** (prefix max = "from the start to i"; suffix max = "from i to the end"). For arbitrary-range max/min you'd need structures you haven't learned yet.

### Traps
- **Overflow:** prefix-sum arrays are almost always `long long`.
- **Bounds:** difference array touches `diff[r+1]` (size `n+2`); 2D touches row/col `0`.
- **Reset** `s[0]=0` and clear arrays between multiple test cases.
- Don't force arbitrary-range **max/min** into a prefix trick — it's wrong, not just slow.

### Complexity
| Technique | Precompute | Per query | Use for |
|---|---|---|---|
| 1D prefix sum | `O(n)` | `O(1)` | any range sum |
| 2D prefix sum | `O(n·m)` | `O(1)` | sub-rectangle sum |
| Difference array | `O(1)`/update | `O(n)` rebuild | many range adds |
| Prefix/suffix extrema | `O(n)` | `O(1)` | range with a fixed end |

*Practice: Mansion (AIO 2007), Alien (AIO 2011).*

---

<div style="page-break-after: always;"></div>

## PAGE 2 — Two Pointers / Sliding Window

**Idea:** neighbouring windows overlap almost entirely. Don't recompute the window — **repair** it: subtract what leaves, add what enters. One pass, `O(N)`.

### Signal — reach for this when you see…
- "**contiguous** subarray/run/segment" that is best/longest/shortest/valid.
- "the **longest/shortest** range satisfying some condition" → variable window.
- "best sum/value over every block of **exactly K**" → fixed window.
- a **monotonic** condition: as the left end moves right, the needed right end never moves back.

### Two flavours — decide first, it's half the battle
| | Fixed window | Variable window (two pointers) |
|---|---|---|
| Width | constant `K` | grows/shrinks |
| Pointers | move **together** | move **independently, forward only** |
| Use when | "best exactly-K block" | "shortest/longest valid range" |
| On enter | `+ a[r]` | `+ a[r]` |
| On leave | `- a[r-K]` | `- a[l]` |
| Example | Mansion (2007) | Wet Chairs (2015) |

### Fixed window — repair, don't recompute
```cpp
long long window = 0;
for (int i = 0; i < K; i++) window += a[i];      // first window O(K)
long long best = window;
for (int i = K; i < N; i++) {
    window += a[i] - a[i-K];                      // leave a[i-K], enter a[i]
    if (window > best) best = window;
}
```

### Variable window — the reusable template
```cpp
long long sum = 0;
int best = 0, l = 0;
for (int r = 0; r < N; r++) {
    sum += a[r];                                  // grow right
    while (sum > B) {                             // shrink left while illegal
        sum -= a[l];
        l++;
    }
    int len = r - l + 1;                          // [l, r] is now valid
    if (len > best) best = len;
}
```
`l` and `r` each only ever move **forward**. Total pointer moves ≤ `2N` → `O(N)`.

### Before you code, answer 3 questions
1. **What summary of the window do I keep?** (a sum, a count, a max…)
2. **How does it update on enter / on leave?** Both must be `O(1)`.
3. **What is the monotonic condition** that lets pointers move forward and never back? If you can't name it, two pointers may be *wrong* here.

### Why it's linear (the amortized argument)
A nested `while` inside a `for` **looks** like `O(N²)`. **Look at the pointers, not the loops:** each pointer advances at most `N` times over the whole run, and its progress is **kept** between iterations — never reset. So total work is `O(N)`. If you ever *reset the fast pointer* per outer step, you silently fall back to `O(N²)`.

### Traps
- **Resetting the right pointer** for each left position — the #1 way to break it. Keep its position across iterations.
- **Recomputing** the whole window instead of repairing it — throws away all the benefit.
- **Off-by-one:** pick `[l, r]` (closed) or `[l, r)` (half-open) up front and stay consistent; half-open usually has fewer `±1` bugs.
- **Forgetting to remove** the leaving element from *every* running count.
- **Empty window** when `l` catches `r` — guard so counts don't go negative.
- **Assuming monotonicity without proof** — if it doesn't hold, the answer is wrong, not just slow.

### One-line summary
Keep a running summary of the current window; move both ends forward only, repairing the summary in `O(1)`; the whole sweep is linear.

*Practice: Mansion (AIO 2007), Wet Chairs (AIO 2015), Alien (AIO 2011).*

---

<div style="page-break-after: always;"></div>

## PAGE 3 — Binary Search & Binary Answers

**Idea:** halve the search range every step → `O(log)`. If the *answer* is **monotonic** — a feasibility check `check(X)` flips from false to true (or true to false) exactly once as `X` grows — then binary-search the answer instead of computing it directly.

### Signal — reach for this when you see…
- a **sorted** array and "does X exist / first ≥ X / last ≤ X / how many ≤ X".
- "**maximise the minimum**" or "**minimise the maximum**" — the giveaway phrase for binary-the-answer.
- "smallest/largest value such that *[something]* is possible", where you can write a `check(X)` that's easier than finding the optimum.
- the answer is a number in a **large range**, and checking a guess is much easier than constructing the best one.

### Plain binary search on a sorted array
Half-open range `[lo, hi)`; result is the first index that satisfies the condition.
```cpp
int lo = 0, hi = n;                    // search space [lo, hi)
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;      // avoid (lo+hi) overflow
    if (a[mid] >= x) hi = mid;         // condition holds → answer is mid or left
    else             lo = mid + 1;     // condition fails → go right
}
// lo = first index with a[lo] >= x   (== n if none)
```

### Binary the answer — the workhorse template
"Smallest `T` that is feasible" (predicate is false…false…**true**…true):
```cpp
long long lo = LO, hi = HI, ans = -1;  // ans stays -1 if nothing feasible
while (lo <= hi) {
    long long mid = lo + (hi - lo) / 2;
    if (check(mid)) { ans = mid; hi = mid - 1; }   // feasible → try smaller
    else            { lo = mid + 1; }              // infeasible → need bigger
}
// ans = smallest feasible T
```
For "**largest** feasible `T`" (true…true…false…false), flip the feasible branch:
`if (check(mid)) { ans = mid; lo = mid + 1; } else hi = mid - 1;`

### Writing `check()` — example: minimise the maximum
"Cut `a[0..n-1]` into at most `K` **contiguous** groups; can every group sum stay `≤ T`?" Bigger `T` ⇒ easier ⇒ once true, stays true (that's the monotonicity that licenses the search).
```cpp
bool check(long long T) {              // greedy feasibility test, O(n)
    int groups = 1;
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > T) return false;    // one element alone exceeds T
        if (cur + a[i] > T) { groups++; cur = 0; }  // start a new group
        cur += a[i];
    }
    return groups <= K;
}
// search bounds: lo = max element, hi = total sum
```

### Before you code, answer 2 questions
1. **Is it monotonic?** State it: "as `T` increases, `check` goes false → true (or true → false), never flips back." No monotonicity ⇒ binary-the-answer is wrong.
2. **What are the bounds?** `lo` and `hi` must bracket the true answer, and one end must be guaranteed feasible / infeasible.

### Traps
- **`mid` overflow:** use `lo + (hi - lo) / 2`, never `(lo + hi) / 2`.
- **Infinite loop / off-by-one:** match the loop shape to the update — `[lo, hi)` with `hi = mid` / `lo = mid + 1`, **or** `lo <= hi` with `ans`-capture and `mid ± 1`. Don't mix the two styles.
- **Wrong direction:** confirm whether `check` is false-then-true or true-then-false, and put `ans =` on the correct branch.
- **Bounds too tight:** if the answer can be "impossible" or the extreme value, make sure `lo`/`hi` still cover it.
- **Real-valued answers:** loop a fixed ~100 iterations (or until `hi - lo < 1e-9`) instead of integer `mid ± 1`.
- **Slow `check`:** total cost is `O(check × log(range))` — keep `check` at `O(n)` or better.

### Complexity
`O(log₂(range) × cost of check)`. Sorted-array search: `O(log n)`. Binary-the-answer over a value range `V` with an `O(n)` check: `O(n log V)`.

*Practice: any "maximise the minimum" / "minimise the maximum" AIO problem; revisit past problems where the naive search over the answer would `O(answer)` — replace it with `O(log answer)`.*

---

<div style="page-break-after: always;"></div>

## PAGE 4 — Greedy

**Idea:** build the answer by repeatedly taking the choice that looks best **right now**, and never reconsider. Fast and simple — but only *correct* when a local-best choice is provably safe. The proof is the hard part, not the code.

### Signal — reach for this when you see…
- "maximise / minimise" where you can **order** the items and then take/skip in that order.
- **scheduling / interval** problems: most non-overlapping intervals, fewest rooms, earliest deadline first.
- "at each step, pick the smallest / largest / closest / earliest …".
- a strong hunch that **sort by some key, then one pass** solves it.

### Method — three steps
1. **Guess a rule** (almost always: sort by some key, then sweep once).
2. **Prove it** with an *exchange argument*: take any optimal solution, show that swapping it one step toward the greedy choice never makes it worse ⇒ greedy is at least as good.
3. **Implement:** sort + single pass. Sorting is the workhorse.

### Classic template — activity selection (max non-overlapping intervals)
Rule: **sort by end time**, take an interval whenever it starts at/after the last taken one's end.
```cpp
#include <iostream>
#include <algorithm>          // for sort
using namespace std;

const int MAXN = 100005;
struct Interval { long long s, e; } iv[MAXN];

bool byEnd(const Interval& x, const Interval& y) { return x.e < y.e; }

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> iv[i].s >> iv[i].e;

    sort(iv, iv + n, byEnd);              // O(n log n): sort by end time
    int count = 0;
    long long lastEnd = -1;               // nothing taken yet (-infinity)
    for (int i = 0; i < n; i++) {
        if (iv[i].s >= lastEnd) {         // doesn't overlap the last chosen
            count++;
            lastEnd = iv[i].e;
        }
    }
    cout << count << "\n";
    return 0;
}
```
Why end-time and not start-time? Finishing earliest leaves the most room for everything after — the exchange argument makes this precise.

### When greedy is right — a quick gut check
- **Sort key is obvious and stable** and each step's best choice can't hurt later steps ⇒ likely greedy.
- If a good choice now can **force a worse choice later** (e.g. 0/1 knapsack, coin change with odd denominations), greedy **fails** — those need dynamic programming (a later topic). Recognise them and don't force greedy.

### Traps
- **No proof, no trust.** On non-obvious problems a plausible rule is often wrong. **Stress-test:** run your greedy against a brute force on random small inputs — mismatches expose a broken rule fast.
- **Wrong sort key.** Choosing *what* to sort by *is* the problem (end vs start, ratio vs value, deadline vs length). Try to break your key with a tiny counterexample.
- **Tie-breaking undefined.** Decide how equal keys order; an unstable choice can change the answer.
- **Overflow.** Sums/products of choices → `long long`.
- **Greedy where DP is needed.** If choices interact, switch tools rather than patching the greedy.

### One-line summary
Sort by the right key, sweep once taking the locally-best safe choice — but only after an exchange argument (or a brute-force stress test) convinces you the local choice is globally safe.

*Practice: interval-scheduling and "sort-then-sweep" AIO problems; whenever you write a greedy, stress-test it against brute force before trusting it.*
