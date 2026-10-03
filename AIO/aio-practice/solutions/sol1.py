# Problem 1: Rover  (SIMULATION)
# Distinct integer positions = max_prefix - min_prefix + 1 ; also final position.
import sys
def main():
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    pos = 0
    mn = 0
    mx = 0
    idx = 1
    for i in range(n):
        pos += int(data[idx]); idx += 1
        if pos < mn: mn = pos
        if pos > mx: mx = pos
    sys.stdout.write(f"{mx - mn + 1} {pos}\n")
main()
