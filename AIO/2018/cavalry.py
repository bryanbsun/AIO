n = int(input())
a = []
for i in range(n):
    a.append(int(input().strip()))

a.sort()

answer = "YES"
p = 0
while p < n:
    e = p + a[p] - 1
    if e >= n or a[e] != a[p]:
        answer = "NO"
        break
    else:
        p = e + 1

print(answer)
