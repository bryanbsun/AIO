# AIO-Style Practice Contest (2026 Set)

A self-contained, AIO-modelled practice contest: **6 problems, 3 hours,
100 points each**, with a full test suite and an automatic judge so students
can mark their own solutions exactly like the real contest.

The format follows the Australian Informatics Olympiad (as run 2022–2025):
six scenario problems of increasing difficulty, each split into subtasks, judged
on standard input / standard output, with an O(n²) solution typically earning
the small-N subtasks and a fully efficient solution needed for full marks.
Problem sizes go up to **N = 200 000**, as in real AIO papers.

## What's in the box
```
aio-practice/
├── README.md                  ← you are here
├── problems/
│   ├── booklet.md             ← all six problems in one file (hand this out)
│   └── problem1..6_*.md       ← individual statements
├── solutions/
│   └── sol1..6.py             ← reference solutions (SPOILERS — model answers)
├── tests/
│   └── p1..6/                 ← NN.in / NN.out for every test case
├── judge.py                   ← self-testing marker (AIO subtask scoring)
├── scoring.json               ← subtask → tests → points, and time limits
├── build_tests.py             ← regenerates the whole test suite
└── verify.py                  ← cross-checks references vs brute force
```

## How students test themselves

Write a program that **reads from stdin and writes to stdout**. Then run the
judge, passing the problem number and the command that runs your program:

```bash
# Python
python3 judge.py 1 "python3 my_rover.py"

# C / C++ (compile first)
g++ -O2 -o sol my_shipping.cpp
python3 judge.py 5 "./sol"

# Java
javac Main.java
python3 judge.py 3 "java Main"

# Mark all six at once — {p} is replaced by the problem number
python3 judge.py all "python3 sol{p}.py"
```

Useful flags:
- `--tl SECONDS` override the per-case time limit (e.g. `--tl 8` when testing
  in slow interpreted languages on a slow machine).
- `--verbose` show the result of every individual test, not just failures.

The judge prints, for each subtask, whether it passed and the points awarded,
plus a per-problem and grand total. A subtask earns its points only if **all**
its tests pass in time — the same rule as the real AIO. Output comparison
ignores surrounding whitespace and treats any run of spaces/newlines as one
separator.

### Example output
```
== Problem 4 ==  (time limit 3.0s per case)
  subtask s1: 20/20  (worst 0.03s, 4 tests)
  subtask s2: 0/30   (worst 2.00s, 2 tests)
      05: TLE  2.00s
  subtask s3: 0/50   (worst 2.00s, 3 tests)
  Problem 4 total: 20/100
```
(An O(n²) sliding-window here passes the small subtask but times out on the
large ones — exactly the intended lesson about complexity.)

## Skill coverage & difficulty distribution

Each of the five requested skills is the star of at least one problem, and the
capstone combines several — mirroring how AIO ramps from a warm-up simulation to
a multi-idea final problem.

| Problem | Primary skill | Also exercises | Difficulty |
|---------|---------------|----------------|-----------|
| 1 Rover | simulation | 64-bit overflow, min/max tracking | easy |
| 2 Rainfall | prefix sums | 64-bit sums, range queries | easy |
| 3 Concerts | greedy | sorting, exchange argument | medium |
| 4 Training | two pointers | sliding window, 64-bit | medium |
| 5 Shipping | binary search on answer | greedy feasibility check | hard |
| 6 Twin Peaks | prefix sums | linear sweep / running max, casework | hard |

Every problem has three subtasks. Subtask 1 is solvable by brute force
(`O(n²)` or exponential) so students who spot only the naive idea still score;
subtask 2 is an intermediate size or reduced value range (often the place where
32-bit overflow or an `O(n²)` blow-up first bites); subtask 3 needs the full
efficient algorithm at `N = 200 000`. Point splits are 30/30/40 for the two easy
problems and 20/30/50 for the four harder ones.

## Test design (boundary, time & space)

Each problem's tests deliberately include:
- **Minimum sizes**: `N = 1`, or `N = L + R`, single-element / single-query cases.
- **Degenerate answers**: everything overlapping (answer 1), everything disjoint
  (answer N), whole array fits / nothing fits, `D = 1`, `D = N`.
- **Overflow stressors**: maximum values at `N = 200 000` so any 32-bit
  accumulator overflows (e.g. Rover with all `+10^9`, Rainfall all `10^9` with
  full-range queries, Training with `K` up to `10^18`).
- **Adversarial structure**: monotonic runs, zig-zags, many equal keys, one huge
  element, so a wrong greedy / early-exit trick fails.
- **Worst-case timing**: maximum-size random inputs that force the intended
  complexity; slower solutions TLE here.

All expected outputs are produced by the reference solutions in `solutions/`,
which were **cross-validated against independent brute-force solvers** on
thousands of random small cases (`python3 verify.py`).

## Regenerating or extending the tests
```bash
python3 build_tests.py     # rebuilds tests/ and scoring.json (deterministic seed)
python3 verify.py          # re-checks references vs brute force
```
`build_tests.py` is also the place to add your own cases: each problem has a
`pN()` function returning `(name, subtask, input_text)` tuples.

## Time limits
The limits in `scoring.json` (3–4 s) are set generously so that a correct
**Python** reference solution passes comfortably on a modest machine. For a real
sit-down contest with C++ you would tighten these to ~1 s; adjust the
`time_limit` fields or pass `--tl`.
