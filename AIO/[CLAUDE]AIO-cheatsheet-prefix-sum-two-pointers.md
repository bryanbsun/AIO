# AIO Tips

## Verdicts

- AC: Accepted (correct)

- WA: Wrong Answer (logic bug/edge case missed)

- TLE: Time Limit Exceeded (too slow, infinite loop possible)

- MLE: Memory Limit Exceeded (rare in Python)

- RE: Runtime Error (crash e.g. index out of range)

- CE: Compile Error (syntax error in Python)

## Strategy

- Speedrun fist 3 problems  then read all problems

- Don't ignore Problem 6- easy subtasks may exist.

- Focus on subtasks - high score/difficulty ratio.

- Brute force solutions often enough for early subtasks

- Solve subtasks incrementally  they often guide the full solution.Clean up easy subtasks before contest ends.

- If WA on brute force  idea is wrong or bug in simple code.

- If AC on brute force - idea correct, easier to extend to full solve



---

<div style="page-break-after: always;"></div>

# Fast Input/Output in C++

**Idea:** `cin`/`cout` are slow by default. Two lines at the top of `main` make them fast enough for `10^6`+ values — do it every contest, every time.

```cpp
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);  // untie C++ streams from C stdio → big speedup
    cin.tie(NULL);                     // don't flush cout before every cin

    int n; cin >> n;                   // now read as usual
    // ...
    return 0;
}
```

## Tips:

- **PUT the two lines first** in `main`, before any input — they make `cin`/`cout` about as fast as `scanf`/`printf`.
- **USE `"\n"`, not `endl`** — `endl` flushes the buffer every call and destroys speed in big output loops.
- **DON'T mix** `cin`/`cout` with `scanf`/`printf` after `sync_with_stdio(false)`.
- **`scanf`/`printf` are a fine alternative** if you prefer C style: `scanf("%lld", &x);` reads a `long long`, `%d` an `int`; print with `printf("%lld\n", x);`.
- **Whitespace is automatic:** `cin >>` skips spaces and newlines, so `cin >> n` then a loop of `cin >> a[i]` works no matter how the input is laid out.
- **Fast reading doesn't fix overflow** — still use `long long` where sums can exceed ~2×10⁹.

---

<div style="page-break-after: always;"></div>

# Prefix Sums

**Idea:** PRECOMPUTE ONECE, then answer *any* range-sum query in `O(1)` with one subtraction.

## Signals:

- "sum / count / total of a **range** `[l, r]`", asked **many times**, or over **many candidate ranges**.
- a fixed array that **does not change**, but ranges you query repeatedly.
- a grid with repeated **sub-rectangle** sum/count queries → 2D version.
- "**apply many range add operations**, then read the array once" → difference array (the inverse).

## 1D prefix sum — the core

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

## Fixed-length window sum (e.g. best K consecutive)

Right endpoint `i` covers `a[i-K+1 .. i]`, whose sum is `s[i] - s[i-K]`:

```cpp
long long best = -1;
for (int i = k; i <= n; i++) {                   // i = window's right end
    long long win = s[i] - s[i-k];
    if (best == -1 || win > best) best = win;
}
```

Turns the naive `O(N·K)` scan into `O(N)`.

## 2D prefix sum — sub-rectangle sums

Build with inclusion–exclusion; 1-indexing makes row/col 0 all zero automatically.

```cpp
for (int i = 1; i <= n; i++)
  for (int j = 1; j <= m; j++)
    s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];

// rectangle with corners (r1,c1) top-left, (r2,c2) bottom-right:
long long sum = s[r2][c2] - s[r1-1][c2] - s[r2][c1-1] + s[r1-1][c1-1];
```

## Difference array — the inverse (many range-adds, read once)

For each "add `v` to `[l, r]`": `diff[l] += v; diff[r+1] -= v;`  Then a prefix sum of `diff` gives the final array. Each update `O(1)`, final rebuild `O(n)`.

---

<div style="page-break-after: always;"></div>

# Two Pointers / Sliding Window

**Idea:** neighbouring windows overlap almost entirely. Don't recompute the window — **repair** it: subtract what leaves, add what enters. One pass, `O(N)`.

## Signals:

- "**contiguous** subarray/run/segment" that is best/longest/shortest/valid.
- "the **longest/shortest** range satisfying some condition" → variable window.
- "best sum/value over every block of **exactly K**" → fixed window.
- a **monotonic** condition: as the left end moves right, the needed right end never moves back.

## Two flavours:

|          | Fixed window           | Variable window (two pointers)       |
| -------- | ---------------------- | ------------------------------------ |
| Width    | constant `K`           | grows/shrinks                        |
| Pointers | move **together**      | move **independently, forward only** |
| Use when | "best exactly-K block" | "shortest/longest valid range"       |
| On enter | `+ a[r]`               | `+ a[r]`                             |
| On leave | `- a[r-K]`             | `- a[l]`                             |

## Fixed window — repair, don't recompute

```cpp
long long window = 0;
for (int i = 0; i < K; i++) window += a[i];      // first window O(K)
long long best = window;
for (int i = K; i < N; i++) {
    window += a[i] - a[i-K];                      // leave a[i-K], enter a[i]
    if (window > best) best = window;
}
```

## Variable window — the reusable template

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

## Before you code, answer 3 questions

1. **What summary of the window do I keep?** (a sum, a count, a max…)
2. **How does it update on enter / on leave?** Both must be `O(1)`.
3. **What is the monotonic condition** that lets pointers move forward and never back? If you can't name it, two pointers may be *wrong* here.

## Tips:

- **DON'T reset the right pointer** for each left position — keep its position across iterations.

- **CHECK empty window** when `l` catches `r` — so counts don't go negative.

- **DON'T assume monotonicity without proof** 

---

<div style="page-break-after: always;"></div>

## Binary Search & Binary Answers

**Idea:** Search the solution space if it's monotonic.  If the solutions not monotonic, prefix-sum, or prefix-maxima/minima can make them monotonic!

### Signals:

- a **sorted** array + "exists / first ≥ / last ≤ / how many ≤ X".
- "**maximise the minimum**" / "**minimise the maximum**" — the classic binary-the-answer phrase.
- "smallest / largest value such that *[something]* is possible", with an easy `check(X)`.
- the answer is a number in a **large range**, and **testing a guess is easier than building the best one**.

### Plain binary search (sorted array)

```cpp
int l = 1, r = n;                    // half-open [lo, hi)
while (l <= r) {
    int mid = l + (r - l) / 2;      // avoid (lo+hi) overflow
    if (a[mid] >= x) r = mid - 1;     
    else             l = mid + 1;     
}
// l = first index with a[l] >= x   (n+1 if none)
```

### Binary the answer

Smallest `T` that works (false…false…**true**…true):

```cpp
long long l = LO, r = HI;  // ans stays -1 if nothing works
while (l <= r) {
    long long mid = l + (r - l) / 2;
    if (check(mid)) r = mid - 1;   // works → try smaller
    else            l = mid + 1;   // fails → need bigger
}
// l = first index that works, (HI + 1 if none)
```

Largest `T` that works: `if (check(mid)) l = mid + 1; else r = mid - 1; // answer is r`

### Writing check() — minimise the maximum

"Cut the array into ≤ `K` contiguous groups, each sum ≤ `T`?" Bigger `T` ⇒ easier ⇒ monotonic.

```cpp
bool check(long long T) {              // O(n) greedy test
    int groups = 1; long long cur = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > T) return false;    // one element alone exceeds T
        if (cur + a[i] > T) { groups++; cur = 0; }  // start a new group
        cur += a[i];
    }
    return groups <= K;
}
```

### Tips:

- **STATE the monotonicity first:** "as `T` grows, `check` goes false→true and never flips back." No monotonicity → wrong tool.
- Use `lo + (hi - lo) / 2` to avoid overflow.
- **REAL-valued answers:** loop ~100 times (or until `hi - lo < 1e-9`) instead of `mid ± 1`.

---

<div style="page-break-after: always;"></div>

# Greedy

**Idea:** repeatedly take the choice that looks best right now, never reconsider. Simple and fast — correct only when a local-best choice is provably safe. The proof is the hard part, not the code.

## Signals:

- "maximise / minimise" where you can **order** items, then take/skip in that order.
- **scheduling / interval** problems (most non-overlapping, fewest rooms, earliest deadline).
- "at each step pick the smallest / largest / earliest / closest …".
- a hunch that **sort by some key, then one pass** solves it.

## Method

1. **Guess** a rule (usually: sort by a key, then sweep).
2. **Prove** it — exchange argument: swapping any optimal solution toward the greedy choice never makes it worse.
3. **Code** it: sort + single pass.

## Template — activity selection (max non-overlapping intervals)

Rule: **sort by end time**, take an interval if it starts at/after the last taken end.

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
    int count = 0; long long lastEnd = -1;
    for (int i = 0; i < n; i++)
        if (iv[i].s >= lastEnd) { count++; lastEnd = iv[i].e; }
    cout << count << "\n";
    return 0;
}
```

Earliest finish leaves the most room for the rest — that's why end-time, not start-time.

### Tips:

- **NO proof, NO trust:** stress-test greedy against brute force on random small inputs — mismatches expose a bad rule fast.
- **THE SORT KEY *is* the problem** (end vs start, ratio vs value) — try to break your key with a tiny counterexample.
- **DEFINE tie-breaking** for equal keys.

- **USE `long long`** for accumulated sums.
