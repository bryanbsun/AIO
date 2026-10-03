ro, bo, s, rp, bp = map(int, input().strip().split())

r = ro - rp
b = bo - bp

answer = 0

if rp == 0:
    answer = s + b + 1
elif bp == 0:
    answer = s + r + 1
elif r >= 0 and b >= 0:
    answer = s + min(r,b) + 1
else:
    answer = s + min(b,0) + min(r, 0) + 1

answer = max(answer, 0)
print(answer)

