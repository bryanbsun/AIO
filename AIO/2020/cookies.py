d,c0 = map(int, input().strip().split())
p1,c1 = map(int, input().strip().split())
p2,c2 = map(int, input().strip().split())

tc = 0
c = c0
bought1, bought2 = False, False

for i in range(1,d+1):
    tc += c

    b1 = c1*(d-i) - p1
    b2 = c2*(d-i) - p2

    if b1 >= b2:
        if b1 > 0 and not bought1 and tc >= p1:
            tc -= p1
            bought1 = True
            c += c1
        if b2 > 0 and not bought2 and tc >= p2:
            tc -= p2
            bought2 = True
            c += c2
    else:
        if b2 > 0 and not bought2 and tc >= p2:
            tc -= p2
            bought2 = True
            c += c2
        if b1 > 0 and not bought1 and tc >= p1:
            tc -= p1
            bought1 = True
            c += c1

answer = tc
print(answer)
