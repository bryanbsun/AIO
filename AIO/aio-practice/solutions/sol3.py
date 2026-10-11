# Problem 3: Concerts  (GREEDY - activity selection)
# Attend max concerts, no overlap; touching endpoints (end == start) allowed.
import sys
def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); idx+=1
    iv = []
    for i in range(n):
        s = int(data[idx]); e = int(data[idx+1]); idx+=2
        iv.append((e, s))
    iv.sort()               # sort by end time
    count = 0
    last_end = -1  # ends are >=0
    first = True
    for e, s in iv:
        if first or s >= last_end:
            count += 1
            last_end = e
            first = False
    sys.stdout.write(f"{count}\n")
main()
