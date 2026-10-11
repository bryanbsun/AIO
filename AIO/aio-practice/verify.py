import random, subprocess, sys, os

SOL = os.path.join('solutions')
def run(sol, inp):
    p = subprocess.run([sys.executable, os.path.join(SOL, sol)],
                       input=inp.encode(), capture_output=True)
    return p.stdout.decode().split()

random.seed(12345)
fails = 0

# ---------- P1 brute ----------
def brute1(n, moves):
    pos=0; visited={0}
    for m in moves:
        step = 1 if m>0 else -1
        for _ in range(abs(m)):
            pos+=step; visited.add(pos)
    return [str(len(visited)), str(pos)]
for _ in range(2000):
    n=random.randint(1,6); moves=[random.choice([x for x in range(-8,9) if x!=0]) for _ in range(n)]
    inp=f"{n}\n"+"\n".join(map(str,moves))+"\n"
    if run('sol1.py',inp)!=brute1(n,moves):
        print("P1 FAIL",inp); fails+=1; break

# ---------- P2 brute ----------
for _ in range(2000):
    n=random.randint(1,8); q=random.randint(1,6)
    r=[random.randint(0,20) for _ in range(n)]
    qs=[]
    for _ in range(q):
        l=random.randint(1,n); rr=random.randint(l,n); qs.append((l,rr))
    inp=f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{l} {rr}" for l,rr in qs)+"\n"
    exp=[str(sum(r[l-1:rr])) for l,rr in qs]
    if run('sol2.py',inp)!=exp:
        print("P2 FAIL",inp); fails+=1; break

# ---------- P3 brute (bitmask) ----------
def brute3(n, iv):
    best=0
    for mask in range(1<<n):
        chosen=[iv[i] for i in range(n) if mask>>i&1]
        chosen.sort()
        ok=True
        for i in range(1,len(chosen)):
            if chosen[i][0] < chosen[i-1][1]:  # start < prev end -> overlap
                ok=False; break
        if ok: best=max(best,len(chosen))
    return [str(best)]
for _ in range(1500):
    n=random.randint(1,11); iv=[]
    for _ in range(n):
        s=random.randint(0,8); e=s+random.randint(1,4); iv.append((s,e))
    inp=f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"
    if run('sol3.py',inp)!=brute3(n,iv):
        print("P3 FAIL",inp,"got",run('sol3.py',inp),"exp",brute3(n,iv)); fails+=1; break

# ---------- P4 brute ----------
def brute4(n,k,a):
    best=0
    for i in range(n):
        s=0
        for j in range(i,n):
            s+=a[j]
            if s<=k: best=max(best,j-i+1)
            else: break
    return [str(best)]
for _ in range(2000):
    n=random.randint(1,12); k=random.randint(1,30); a=[random.randint(1,10) for _ in range(n)]
    inp=f"{n} {k}\n"+" ".join(map(str,a))+"\n"
    if run('sol4.py',inp)!=brute4(n,k,a):
        print("P4 FAIL",inp); fails+=1; break

# ---------- P5 brute (DP) ----------
def brute5(n,d,w):
    import math
    INF=float('inf')
    pre=[0]*(n+1)
    for i in range(n): pre[i+1]=pre[i]+w[i]
    dp=[[INF]*(d+1) for _ in range(n+1)]
    dp[0][0]=0
    for i in range(1,n+1):
        for parts in range(1,d+1):
            for j in range(parts-1,i):
                seg=pre[i]-pre[j]
                val=max(dp[j][parts-1],seg)
                if val<dp[i][parts]: dp[i][parts]=val
    return [str(dp[n][d])]
for _ in range(1500):
    n=random.randint(1,9); d=random.randint(1,n); w=[random.randint(1,12) for _ in range(n)]
    inp=f"{n} {d}\n"+" ".join(map(str,w))+"\n"
    if run('sol5.py',inp)!=brute5(n,d,w):
        print("P5 FAIL",inp,"got",run('sol5.py',inp),"exp",brute5(n,d,w)); fails+=1; break

# ---------- P6 brute ----------
def brute6(n,L,R,a):
    NEG=-1
    def wsum(s,l): return sum(a[s:s+l])
    best=NEG
    for i in range(0,n-L+1):
        for j in range(0,n-R+1):
            # non-overlap: [i,i+L) and [j,j+R)
            if i+L<=j or j+R<=i:
                best=max(best,wsum(i,L)+wsum(j,R))
    return [str(best)]
for _ in range(1500):
    n=random.randint(2,12)
    L=random.randint(1,n-1); R=random.randint(1,n-L)
    a=[random.randint(0,15) for _ in range(n)]
    inp=f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"
    if run('sol6.py',inp)!=brute6(n,L,R,a):
        print("P6 FAIL",inp,"got",run('sol6.py',inp),"exp",brute6(n,L,R,a)); fails+=1; break

print("ALL VERIFIED OK" if fails==0 else f"{fails} FAILURES")
