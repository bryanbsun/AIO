# Generators

The authoritative test generator is **`../build_tests.py`** (run it from the
project root). It builds every `.in`, produces each `.out` with the matching
reference solution, and writes `scoring.json`.

To add cases for problem *k*, edit the `pk()` function in `build_tests.py`. Each
entry is a tuple `(name, subtask, input_text)` where `subtask` is `"s1"`,
`"s2"`, or `"s3"`. Re-run `python3 build_tests.py` to regenerate.

Design guidance used here (reuse it for new cases):
- always include the smallest legal input and the largest (`N = 200000`);
- include a case whose answer is an extreme (all/none, min/max);
- include a maximum-value case that overflows 32-bit accumulators;
- include an adversarial structure (sorted, zig-zag, many ties, one outlier);
- keep at least one full-size random case per hard subtask for timing.
