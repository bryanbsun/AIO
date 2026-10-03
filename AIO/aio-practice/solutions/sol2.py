# Problem 2: Rainfall  (PREFIX SUM)
import sys
def main():
    data = sys.stdin.buffer.read().split()
    idx = 0
    n = int(data[idx]); idx+=1
    q = int(data[idx]); idx+=1
    pre = [0]*(n+1)
    for i in range(1, n+1):
        pre[i] = pre[i-1] + int(data[idx]); idx+=1
    out = []
    for _ in range(q):
        l = int(data[idx]); idx+=1
        r = int(data[idx]); idx+=1
        out.append(str(pre[r] - pre[l-1]))
    sys.stdout.write("\n".join(out) + "\n")
main()
