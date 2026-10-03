#!/usr/bin/env python3
"""
AIO-Practice self-testing judge.

USAGE
    python3 judge.py <problem> "<run-command>" [--tl SECONDS] [--verbose]

EXAMPLES
    python3 judge.py 1 "python3 my_p1.py"
    python3 judge.py 4 "./a.out"                 # a compiled C/C++ binary
    python3 judge.py 5 "java Main" --tl 6
    python3 judge.py all "python3 sol{p}.py"     # {p} is replaced by the problem number

The command reads a test case from STANDARD INPUT and writes its answer to
STANDARD OUTPUT, exactly like the real AIO judge. Output comparison ignores
leading/trailing whitespace and treats any run of spaces/newlines as one
separator (same leniency the AIO grader gives).

SCORING (AIO style): each problem is worth 100 points split across subtasks.
A subtask scores its full points only if EVERY test in it passes within the
time limit; otherwise it scores 0.
"""
import sys, os, json, shlex, subprocess, time

ROOT = os.path.dirname(os.path.abspath(__file__))
TESTS = os.path.join(ROOT, "tests")
SCORING = os.path.join(ROOT, "scoring.json")

G = "\033[92m"; R = "\033[91m"; Y = "\033[93m"; B = "\033[1m"; X = "\033[0m"
if not sys.stdout.isatty():
    G = R = Y = B = X = ""

def tokenize(s):
    return s.split()

def run_case(cmd, in_path, tl):
    with open(in_path, "rb") as f:
        data = f.read()
    start = time.perf_counter()
    try:
        p = subprocess.run(cmd, input=data, capture_output=True, timeout=tl)
    except subprocess.TimeoutExpired:
        return ("TLE", tl, b"")
    dt = time.perf_counter() - start
    if p.returncode != 0:
        return ("RTE", dt, p.stderr)
    return ("OK", dt, p.stdout)

def judge_problem(pid, cmd, manifest, tl_override, verbose):
    info = manifest[str(pid)]
    tl = tl_override if tl_override else info["time_limit"]
    tdir = os.path.join(TESTS, f"p{pid}")
    print(f"\n{B}== Problem {pid} =={X}  (time limit {tl:.1f}s per case)")
    total = 0
    for sub in info["subtasks"]:
        all_pass = True
        detail = []
        worst = 0.0
        for name in sub["tests"]:
            in_path = os.path.join(tdir, name + ".in")
            out_path = os.path.join(tdir, name + ".out")
            with open(out_path) as f:
                expected = tokenize(f.read())
            status, dt, got = run_case(cmd, in_path, tl)
            worst = max(worst, dt)
            if status == "TLE":
                all_pass = False; detail.append((name, f"{R}TLE{X}", dt)); continue
            if status == "RTE":
                all_pass = False; detail.append((name, f"{R}RTE{X}", dt)); continue
            if tokenize(got.decode(errors="replace")) == expected:
                detail.append((name, f"{G}AC{X}", dt))
            else:
                all_pass = False; detail.append((name, f"{R}WA{X}", dt))
        pts = sub["points"] if all_pass else 0
        total += pts
        mark = f"{G}" if all_pass else f"{R}"
        print(f"  subtask {sub['name']}: {mark}{pts}/{sub['points']}{X}  "
              f"(worst {worst:.2f}s, {len(sub['tests'])} tests)")
        if verbose or not all_pass:
            for name, st, dt in detail:
                print(f"      {name}: {st}  {dt:.2f}s")
    print(f"  {B}Problem {pid} total: {total}/100{X}")
    return total

def main():
    args = sys.argv[1:]
    if len(args) < 2:
        print(__doc__); sys.exit(1)
    tl_override = None; verbose = False
    pos = []
    i = 0
    while i < len(args):
        if args[i] == "--tl":
            tl_override = float(args[i+1]); i += 2
        elif args[i] == "--verbose":
            verbose = True; i += 1
        else:
            pos.append(args[i]); i += 1
    problem = pos[0]
    cmd_template = pos[1]
    with open(SCORING) as f:
        manifest = json.load(f)

    if problem == "all":
        grand = 0
        for pid in range(1, 7):
            cmd = shlex.split(cmd_template.replace("{p}", str(pid)))
            grand += judge_problem(pid, cmd, manifest, tl_override, verbose)
        print(f"\n{B}==== GRAND TOTAL: {grand}/600 ===={X}")
    else:
        pid = int(problem)
        cmd = shlex.split(cmd_template.replace("{p}", str(pid)))
        judge_problem(pid, cmd, manifest, tl_override, verbose)

if __name__ == "__main__":
    main()
