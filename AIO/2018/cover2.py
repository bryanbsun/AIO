n, k = map(int, input().strip().split())
d = []
for i in range(n-1):
    d.append(int(input()))

for i in range(1, n-1):
    d[i] += d[i-1]

maxcover = d[k-1]
for i in range(1, n-k):
    maxcover = min(maxcover, d[i+k-1]-d[i-1])

print(maxcover)