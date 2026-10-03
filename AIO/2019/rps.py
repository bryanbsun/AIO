import sys
sys.setrecursionlimit(1000000000)

answer = 0

n = int(input().strip())
ra, pa, sa = map(int, input().strip().split())
rb, pb, sb = map(int, input().strip().split())

w1 = min(ra,pb) 
w2 = min(pa, sb) 
w3 = min(sa, rb)
answer += w1 + w2 + w3

ra -= w1
pb -= w1
pa -= w2
sb -= w2
sa -= w3
rb -= w3

d1 = min(ra,rb)
d2 = min(pa,pb)
d3 = min(sa,sb)

ra -= d1
rb -= d1
pa -= d2
pb -= d2
sa -= d3
sb -= d3

answer -= (ra+pa+sa)
'''
if ra > pb:
    answer += pb
else:
    answer += ra
if pa > sb:
    answer += sb
else:
    answer += pa
if sa > rb:
    answer += rb
else:
    answer += sa

if ra-pb-rb > sb:   // pb+rb = N - sb, ra-pb-rb = ra-(pb+rb) = ra - N + sb
    answer -= sb
else: 
    answer -= max(ra-pb-rb,0)
if pa-sb-pb > rb:
    answer -= rb
else:
    answer -= max(pa-sb-pb,0)
if sa-rb-sb > pb:
    answer -= pb
else:
    answer -= max(sa-rb-sb,0)
'''
# Write the answer.
print(answer)
