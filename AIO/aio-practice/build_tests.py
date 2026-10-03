import random, os, subprocess, sys, json

random.seed(2026)
ROOT = os.path.dirname(os.path.abspath(__file__))
TESTS = os.path.join(ROOT, 'tests')
SOL = os.path.join(ROOT, 'solutions')

MAXN = 200000

def write_in(pid, name, text):
    d = os.path.join(TESTS, f"p{pid}")
    os.makedirs(d, exist_ok=True)
    with open(os.path.join(d, name + ".in"), "w") as f:
        f.write(text)

def make_out(pid, name):
    d = os.path.join(TESTS, f"p{pid}")
    with open(os.path.join(d, name + ".in")) as f:
        inp = f.read()
    p = subprocess.run([sys.executable, os.path.join(SOL, f"sol{pid}.py")],
                       input=inp.encode(), capture_output=True)
    with open(os.path.join(d, name + ".out"), "w") as f:
        f.write(p.stdout.decode())

# manifest[pid] = {"time_limit":.., "subtasks":[{"name","points","tests":[...]}]}
manifest = {}

# ---------------- P1 Rover ----------------
def p1():
    specs = []  # (name, subtask, text)
    # s1: N<=1000 |m|<=1000
    specs.append(("01","s1", "1\n1000\n"))                       # single move
    specs.append(("02","s1", "3\n5\n-8\n2\n"))                   # sample
    n=1000; mv=[random.choice([x for x in range(-1000,1001) if x]) for _ in range(n)]
    specs.append(("03","s1", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    # s2: N<=2e5 |m|<=1000
    n=MAXN; mv=[random.choice([x for x in range(-1000,1001) if x]) for _ in range(n)]
    specs.append(("04","s2", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    n=MAXN; mv=[1000]*n                                          # monotonic
    specs.append(("05","s2", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    # s3: full |m|<=1e9
    specs.append(("06","s3", "1\n1000000000\n"))                 # overflow single
    n=MAXN; mv=[1000000000]*n                                    # extreme + overflow
    specs.append(("07","s3", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    n=MAXN; mv=[(10**9 if i%2==0 else -10**9) for i in range(n)] # zigzag extremes
    specs.append(("08","s3", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    n=MAXN; mv=[random.randint(-10**9,10**9) or 1 for _ in range(n)]
    specs.append(("09","s3", f"{n}\n"+"\n".join(map(str,mv))+"\n"))
    return specs

# ---------------- P2 Rainfall ----------------
def p2():
    specs=[]
    specs.append(("01","s1","1 1\n5\n1 1\n"))
    specs.append(("02","s1","5 3\n2 4 1 3 5\n1 3\n2 5\n4 4\n"))
    n=2000;q=2000
    r=[random.randint(0,1000) for _ in range(n)]
    qs=[(lambda l:(l,random.randint(l,n)))(random.randint(1,n)) for _ in range(q)]
    specs.append(("03","s1",f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{a} {b}" for a,b in qs)+"\n"))
    # s2 big small values
    n=MAXN;q=MAXN
    r=[random.randint(0,1000) for _ in range(n)]
    qs=[(lambda l:(l,random.randint(l,n)))(random.randint(1,n)) for _ in range(q)]
    specs.append(("04","s2",f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{a} {b}" for a,b in qs)+"\n"))
    # s3 full-range overflow: all queries (1,N), r max
    n=MAXN;q=MAXN
    r=[10**9]*n
    qs=[(1,n)]*q
    specs.append(("05","s3",f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{a} {b}" for a,b in qs)+"\n"))
    # s3 full random large values
    n=MAXN;q=MAXN
    r=[random.randint(0,10**9) for _ in range(n)]
    qs=[(lambda l:(l,random.randint(l,n)))(random.randint(1,n)) for _ in range(q)]
    specs.append(("06","s3",f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{a} {b}" for a,b in qs)+"\n"))
    # s3 single element queries
    n=MAXN;q=MAXN
    r=[random.randint(0,10**9) for _ in range(n)]
    qs=[(lambda i:(i,i))(random.randint(1,n)) for _ in range(q)]
    specs.append(("07","s3",f"{n} {q}\n"+" ".join(map(str,r))+"\n"+"\n".join(f"{a} {b}" for a,b in qs)+"\n"))
    return specs

# ---------------- P3 Concerts ----------------
def p3():
    specs=[]
    specs.append(("01","s1","1\n0 5\n"))
    specs.append(("02","s1","4\n1 3\n2 5\n4 6\n6 7\n"))
    # all overlapping -> 1
    n=20; iv=[(0,1000000000-i) for i in range(n)]
    specs.append(("03","s1",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    # s2 N<=2000 touching endpoints chain -> all
    n=2000; iv=[(i,i+1) for i in range(n)]
    specs.append(("04","s2",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    n=2000; iv=[]
    for _ in range(n):
        s=random.randint(0,10**9-1); e=random.randint(s+1,min(10**9,s+1000)); iv.append((s,e))
    specs.append(("05","s2",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    # s3 big
    n=MAXN; iv=[(i,i+1) for i in range(n)]              # disjoint touching -> N
    specs.append(("06","s3",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    n=MAXN; iv=[(0,10**9) for _ in range(n)]            # all identical big -> 1
    specs.append(("07","s3",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    n=MAXN; iv=[]
    for _ in range(n):
        s=random.randint(0,10**9-1); e=random.randint(s+1,min(10**9,s+100000)); iv.append((s,e))
    specs.append(("08","s3",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    # many equal end times
    n=MAXN; iv=[]
    for _ in range(n):
        s=random.randint(0,999999); iv.append((s,1000000))
    specs.append(("09","s3",f"{n}\n"+"\n".join(f"{s} {e}" for s,e in iv)+"\n"))
    return specs

# ---------------- P4 Training ----------------
def p4():
    specs=[]
    specs.append(("01","s1","1 5\n10\n"))                        # single > K -> 0
    specs.append(("02","s1","1 5\n5\n"))                         # single == K -> 1
    specs.append(("03","s1","6 8\n3 1 4 1 5 2\n"))              # sample -> 3
    n=2000; a=[random.randint(1,1000) for _ in range(n)]; k=random.randint(1,20000)
    specs.append(("04","s1",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    # s2 big small vals
    n=MAXN; a=[random.randint(1,1000) for _ in range(n)]; k=random.randint(1,10**9)
    specs.append(("05","s2",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[1]*n; k=10**9                                     # whole array <=K -> N
    specs.append(("06","s2",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    # s3 full big vals + 64-bit K
    n=MAXN; a=[random.randint(1,10**9) for _ in range(n)]; k=random.randint(1,10**18)
    specs.append(("07","s3",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[10**9]*n; k=10**18                               # K huge -> N (2e5*1e9=2e14<1e18)
    specs.append(("08","s3",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[10**9]*n; k=1                                     # all > K -> 0
    specs.append(("09","s3",f"{n} {k}\n"+" ".join(map(str,a))+"\n"))
    return specs

# ---------------- P5 Shipping ----------------
def p5():
    specs=[]
    specs.append(("01","s1","1 1\n7\n"))                         # -> 7
    specs.append(("02","s1","5 2\n3 6 7 11 5\n"))              # sample -> 16
    n=20; w=[random.randint(1,50) for _ in range(n)]; d=random.randint(1,n)
    specs.append(("03","s1",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    # s2
    n=2000; w=[random.randint(1,10**6) for _ in range(n)]; d=random.randint(1,n)
    specs.append(("04","s2",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    n=2000; w=[random.randint(1,10**6) for _ in range(n)]; d=1   # -> sum
    specs.append(("05","s2",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    # s3
    n=MAXN; w=[random.randint(1,10**9) for _ in range(n)]; d=random.randint(2,n-1)
    specs.append(("06","s3",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    n=MAXN; w=[random.randint(1,10**9) for _ in range(n)]; d=n   # -> max(w)
    specs.append(("07","s3",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    n=MAXN; w=[1000]*n; d=7                                      # equal weights
    specs.append(("08","s3",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    n=MAXN; w=[1]*n; w[0]=10**9; d=3                            # one huge weight
    specs.append(("09","s3",f"{n} {d}\n"+" ".join(map(str,w))+"\n"))
    return specs

# ---------------- P6 Twin Peaks ----------------
def p6():
    specs=[]
    specs.append(("01","s1","2 1 1\n7 4\n"))                     # minimal N=L+R
    specs.append(("02","s1","6 1 2\n4 1 3 2 5 1\n"))           # sample -> 11
    n=400; a=[random.randint(0,1000) for _ in range(n)]; L=random.randint(1,50); R=random.randint(1,50)
    specs.append(("03","s1",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    # s2
    n=5000; a=[random.randint(0,10**6) for _ in range(n)]; L=random.randint(1,1000); R=random.randint(1,1000)
    specs.append(("04","s2",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    # s3
    n=MAXN; a=[random.randint(0,10**9) for _ in range(n)]; L=random.randint(1,90000); R=random.randint(1,90000)
    specs.append(("05","s3",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[10**9]*n; L=1; R=1                               # all equal, tiny windows
    specs.append(("06","s3",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[10**9]*n; L=100000; R=100000                    # windows fill array exactly
    specs.append(("07","s3",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    n=MAXN; a=[random.randint(0,10**9) for _ in range(n)]; L=1; R=n-1  # extreme asymmetry
    specs.append(("08","s3",f"{n} {L} {R}\n"+" ".join(map(str,a))+"\n"))
    return specs

POINTS = {
    1: {"s1":30,"s2":30,"s3":40},
    2: {"s1":30,"s2":30,"s3":40},
    3: {"s1":20,"s2":30,"s3":50},
    4: {"s1":20,"s2":30,"s3":50},
    5: {"s1":20,"s2":30,"s3":50},
    6: {"s1":20,"s2":30,"s3":50},
}
TIME_LIMIT = {1:3.0,2:4.0,3:4.0,4:3.0,5:4.0,6:4.0}  # generous for self-testing (Python)

builders = {1:p1,2:p2,3:p3,4:p4,5:p5,6:p6}

for pid in range(1,7):
    specs = builders[pid]()
    # group tests by subtask
    order = {}
    for name, sub, text in specs:
        write_in(pid, name, text)
        make_out(pid, name)
        order.setdefault(sub, []).append(name)
    subtasks=[]
    for sub in ("s1","s2","s3"):
        subtasks.append({"name":sub,"points":POINTS[pid][sub],"tests":order.get(sub,[])})
    manifest[str(pid)] = {"time_limit":TIME_LIMIT[pid],"subtasks":subtasks}
    print(f"P{pid}: {len(specs)} tests built")

with open(os.path.join(ROOT,"scoring.json"),"w") as f:
    json.dump(manifest,f,indent=2)
print("scoring.json written")
