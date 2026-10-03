# Problem 4: Training  (TWO POINTERS / sliding window)
# Longest contiguous block with total effort <= K. (all a_i > 0)
import sys
def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); idx+=1
    k = int(data[idx]); idx+=1
    a = data[idx:idx+n]
    a = [int(x) for x in a]
    best = 0
    s = 0          # window sum
    left = 0
    for right in range(n):
        s += a[right]
        while s > k and left <= right:
            s -= a[left]; left += 1
        if right - left + 1 > best:
            best = right - left + 1
    sys.stdout.write(f"{best}\n")
main()
