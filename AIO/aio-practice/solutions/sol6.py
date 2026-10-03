# Problem 6: Twin Peaks  (PREFIX SUM + sweep) -- capstone
# Two non-overlapping windows of lengths L and R, maximise total sum.
import sys
def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); idx+=1
    L = int(data[idx]); idx+=1
    R = int(data[idx]); idx+=1
    a = [int(data[idx+i]) for i in range(n)]
    P = [0]*(n+1)
    for i in range(n):
        P[i+1] = P[i] + a[i]

    NEG = -(1<<62)
    def best_order(len1, len2):
        # window1 (len1) strictly before window2 (len2)
        if len1 + len2 > n:
            return NEG
        # w1[s] = sum of window length len1 starting at s, s in 0..n-len1
        m1 = n - len1
        # prefix max of window1 sums
        bestw1 = [0]*(m1+1)
        run = NEG
        for s in range(m1+1):
            val = P[s+len1] - P[s]
            if val > run: run = val
            bestw1[s] = run
        best = NEG
        for s2 in range(len1, n - len2 + 1):
            k = s2 - len1
            cur = bestw1[k] + (P[s2+len2] - P[s2])
            if cur > best: best = cur
        return best

    ans = max(best_order(L, R), best_order(R, L))
    sys.stdout.write(f"{ans}\n")
main()
