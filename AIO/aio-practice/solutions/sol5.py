# Problem 5: Shipping  (BINARY SEARCH on answer + GREEDY feasibility)
# Split sequence into D contiguous groups; minimise the maximum group sum.
import sys
def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); idx+=1
    d = int(data[idx]); idx+=1
    w = [int(data[idx+i]) for i in range(n)]
    lo = max(w)
    hi = sum(w)
    def days_needed(cap):
        days = 1
        cur = 0
        for x in w:
            if cur + x > cap:
                days += 1
                cur = x
            else:
                cur += x
        return days
    while lo < hi:
        mid = (lo + hi) // 2
        if days_needed(mid) <= d:
            hi = mid
        else:
            lo = mid + 1
    sys.stdout.write(f"{lo}\n")
main()
