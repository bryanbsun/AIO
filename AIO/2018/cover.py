n, k = map(int, input().strip().split())
d = []
for i in range(n-1):
    d.append(int(input()))

cover = 0
for i in range(k):
    cover += d[i]

maxcover = cover
for i in range(1, n-k):
    cover += d[i+k-1] - d[i-1]
    maxcover = min(maxcover, cover)

print(maxcover)