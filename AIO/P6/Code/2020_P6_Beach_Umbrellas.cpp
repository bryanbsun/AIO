// AIO 2020 P6 - Beach Umbrellas
// Method: merge intervals + Greedy (place umbrellas left to right) + Exchange Argument (candidate left ends)
//       + segment tree over remainders (to find jumps) + Binary Lifting (how far j umbrellas can reach)
#include <bits/stdc++.h>
using namespace std;

struct seg{
    long long a, b;
}iv[100010];

long long N, K, X;
int U, m;                           // m: number of blocks after merging
long long st[100010], en[100010];   // block t is [st[t], en[t]]

// node t (1..m): the gap starting at en[t]+1, right after block t; node 0: position 1 (if not covered)
// node E = m+1: the end of the beach N has been reached
int E;
long long pos[100010];              // position of each node, -1 if the node does not exist
int nxt[100010];                    // placing umbrellas back to back from this gap start, which node we jump to
long long cst[100010];              // umbrellas used by this jump
long long dist[100010];             // fewest umbrellas needed to reach N from this node
int up[18][100010];                 // binary lifting: where 2^p jumps lead
long long uc[18][100010];           // binary lifting: total umbrellas used by 2^p jumps

long long rs[100010];               // all gap starts mod X (sorted, duplicates removed)
int nr;
int tr[400010];                     // segment tree: the smallest block index on each remainder

bool cmp(seg p, seg q){
    if (p.a != q.a)
        return p.a < q.a;
    return p.b < q.b;
}

// index of the first value >= v in rs
int firstGE(long long v){
    int l = 1, r = nr;
    while (l <= r){
        int mid = (l + r) / 2;
        if (rs[mid] < v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}

// index of the last value <= v in rs
int lastLE(long long v){
    int l = 1, r = nr;
    while (l <= r){
        int mid = (l + r) / 2;
        if (rs[mid] <= v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}

// segment tree: range [ql, qr] takes min with v
void update(int k, int l, int r, int ql, int qr, int v){
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr){
        tr[k] = min(tr[k], v);
        return;
    }
    int mid = (l + r) / 2;
    update(2 * k, l, mid, ql, qr, v);
    update(2 * k + 1, mid + 1, r, ql, qr, v);
}

// segment tree: point query (minimum along the root-to-leaf path)
int query(int k, int l, int r, int p){
    if (l == r)
        return tr[k];
    int mid = (l + r) / 2;
    if (p <= mid)
        return min(tr[k], query(2 * k, l, mid, p));
    return min(tr[k], query(2 * k + 1, mid + 1, r, p));
}

// mark block t on the remainder range [lo, hi]
void paint(long long lo, long long hi, int t){
    int a = firstGE(lo), b = lastLE(hi);
    if (a <= b)
        update(1, 1, nr, a, b, t);
}

// all positions covered by block t, taken mod X, form one "arc"
void paintBlock(int t){
    if (en[t] - st[t] + 1 >= X){
        paint(0, X - 1, t);
        return;
    }
    long long lo = st[t] % X, hi = en[t] % X;
    if (lo <= hi)
        paint(lo, hi, t);
    else{
        paint(lo, X - 1, t);
        paint(0, hi, t);
    }
}

// starting from gap start a = pos[t], umbrellas go at a, a+X, a+2X, ...
// the first block to the right containing a position congruent to a (mod X) is where we first "land in a block"
void jump(int t){
    long long a = pos[t];
    int h = query(1, 1, nr, firstGE(a % X));
    if (h == INT_MAX){                  // never lands in a block before the end of the beach
        nxt[t] = E;
        cst[t] = (N - a + X) / X;       // ceil((N - a + 1) / X)
    }else{
        cst[t] = (st[h] - a + X - 1) / X;
        if (en[h] == N)
            nxt[t] = E;
        else
            nxt[t] = h;
    }
}

// the rightmost position covered starting from node t with j umbrellas (known not to reach N)
long long runEnd(int t, long long j){
    for (int p = 17; p >= 0; p --)
        if (up[p][t] != E && uc[p][t] <= j){
            j -= uc[p][t];
            t = up[p][t];
        }
    return pos[t] + j * X - 1;          // the remaining j umbrellas go back to back in this gap
}

// the longest coverage when the left side starts at ls (a block start or position 1) and the right side starts from node t
long long value(long long ls, int t){
    long long need = (t == E) ? 0 : dist[t];
    if (need > K)                                   // cannot reach N: put them all on the right
        return runEnd(t, K) - ls + 1;

    // option A: use exactly need umbrellas on the right to reach N, put the rest on the left
    long long left = K - need;
    long long best = N - max(1LL, ls - left * X) + 1;
    // option B: use 1 fewer on the right (the last one may be cut off at N), 1 more on the left
    if (need >= 1){
        long long r = runEnd(t, need - 1);
        best = max(best, r - max(1LL, ls - (left + 1) * X) + 1);
    }
    return best;
}

int main(){
    cin >> N >> U >> K >> X;
    for (int i = 1; i <= U; i ++)
        cin >> iv[i].a >> iv[i].b;
    sort(iv + 1, iv + U + 1, cmp);

    // 1) merge intervals (overlapping or adjacent ones are merged)
    for (int i = 1; i <= U; i ++){
        if (m > 0 && iv[i].a <= en[m] + 1)
            en[m] = max(en[m], iv[i].b);
        else{
            m ++;
            st[m] = iv[i].a;
            en[m] = iv[i].b;
        }
    }

    // 2) nodes
    E = m + 1;
    for (int t = 0; t <= E; t ++){
        pos[t] = -1;
        nxt[t] = E;
    }
    for (int t = 1; t <= m; t ++)
        if (en[t] < N)
            pos[t] = en[t] + 1;
    if (st[1] > 1)
        pos[0] = 1;

    // 3) remainders of the gap starts, sorted with duplicates removed
    for (int t = 0; t <= m; t ++)
        if (pos[t] >= 0)
            rs[++ nr] = pos[t] % X;
    if (nr == 0){                       // no gaps: the whole beach is already covered
        cout << N << endl;
        return 0;
    }
    sort(rs + 1, rs + nr + 1);
    int k = 0;
    for (int i = 1; i <= nr; i ++)
        if (i == 1 || rs[i] != rs[i-1])
            rs[++ k] = rs[i];
    nr = k;
    fill(tr, tr + 4 * nr + 4, INT_MAX);

    // 4) right to left: first compute the jump from the gap start, then paint block t into the segment tree
    for (int t = m; t >= 1; t --){
        if (pos[t] >= 0)
            jump(t);
        paintBlock(t);
    }
    if (pos[0] >= 0)
        jump(0);

    // 5) dist: fewest umbrellas to reach N (jumps only go right, so compute right to left)
    for (int t = m; t >= 1; t --)
        if (pos[t] >= 0)
            dist[t] = cst[t] + (nxt[t] == E ? 0 : dist[nxt[t]]);
    if (pos[0] >= 0)
        dist[0] = cst[0] + (nxt[0] == E ? 0 : dist[nxt[0]]);

    // 6) binary lifting table
    for (int t = 0; t <= E; t ++){
        up[0][t] = E;
        uc[0][t] = 0;
        if (t < E && pos[t] >= 0){
            up[0][t] = nxt[t];
            uc[0][t] = cst[t];
        }
    }
    for (int p = 1; p < 18; p ++)
        for (int t = 0; t <= E; t ++){
            up[p][t] = up[p-1][up[p-1][t]];
            uc[p][t] = min(4000000000000000000LL, uc[p-1][t] + uc[p-1][up[p-1][t]]);
        }

    // 7) try every candidate left end: each block start, plus position 1
    long long ans = 0;
    for (int t = 1; t <= m; t ++)
        ans = max(ans, value(st[t], en[t] == N ? E : t));
    if (pos[0] >= 0)
        ans = max(ans, value(1, 0));

    cout << ans << endl;
    return 0;
}
