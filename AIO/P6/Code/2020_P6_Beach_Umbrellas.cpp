// AIO 2020 P6 - Beach Umbrellas
// 方法：合并区间 + Greedy（从左往右放伞）+ Exchange Argument（候选左端点）
//       + 按余数的线段树（求跳转）+ Binary Lifting（倍增：用 j 把伞能走多远）
#include <bits/stdc++.h>
using namespace std;

struct seg{
    long long a, b;
}iv[100010];

long long N, K, X;
int U, m;                           // m：合并后的 block 个数
long long st[100010], en[100010];   // 第 t 个 block 是 [st[t], en[t]]

// 结点 t (1..m)：block t 之后的空格起点 en[t]+1；结点 0：位置 1（如果没被覆盖）
// 结点 E = m+1：表示已经到达海滩尽头 N
int E;
long long pos[100010];              // 结点对应的位置，-1 表示没有这个结点
int nxt[100010];                    // 从这个空格起点连续放伞，跳到哪个结点
long long cst[100010];              // 这一跳用几把伞
long long dist[100010];             // 从这个结点出发，到达 N 最少要几把伞
int up[18][100010];                 // 倍增：跳 2^p 次到哪
long long uc[18][100010];           // 倍增：跳 2^p 次一共用几把伞

long long rs[100010];               // 所有空格起点 mod X 的值（排序去重）
int nr;
int tr[400010];                     // 线段树：每个余数上最小的 block 编号

bool cmp(seg p, seg q){
    if (p.a != q.a)
        return p.a < q.a;
    return p.b < q.b;
}

// rs 中第一个 >= v 的下标
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

// rs 中最后一个 <= v 的下标
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

// 线段树：区间 [ql, qr] 对 v 取 min
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

// 线段树：单点查询（从根到叶子路径上的最小值）
int query(int k, int l, int r, int p){
    if (l == r)
        return tr[k];
    int mid = (l + r) / 2;
    if (p <= mid)
        return min(tr[k], query(2 * k, l, mid, p));
    return min(tr[k], query(2 * k + 1, mid + 1, r, p));
}

// 在余数区间 [lo, hi] 上标记 block t
void paint(long long lo, long long hi, int t){
    int a = firstGE(lo), b = lastLE(hi);
    if (a <= b)
        update(1, 1, nr, a, b, t);
}

// block t 覆盖的所有位置 mod X，是一段"弧"
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

// 从空格起点 a = pos[t] 出发，伞放在 a, a+X, a+2X, ...
// 右边第一个包含与 a 同余位置的 block，就是第一次"落进 block"的地方
void jump(int t){
    long long a = pos[t];
    int h = query(1, 1, nr, firstGE(a % X));
    if (h == INT_MAX){                  // 一直到海滩尽头都没落进 block
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

// 从结点 t 出发、用 j 把伞（已知到不了 N），能覆盖到的最右位置
long long runEnd(int t, long long j){
    for (int p = 17; p >= 0; p --)
        if (up[p][t] != E && uc[p][t] <= j){
            j -= uc[p][t];
            t = up[p][t];
        }
    return pos[t] + j * X - 1;          // 剩下的 j 把在这个空格里连着放
}

// 左边从 ls（block 起点或位置 1）开始、右边从结点 t 出发时，最长能覆盖多少
long long value(long long ls, int t){
    long long need = (t == E) ? 0 : dist[t];
    if (need > K)                                   // 到不了 N：全放右边
        return runEnd(t, K) - ls + 1;

    // 方案 A：右边刚好用 need 把到 N，剩下的全放左边
    long long left = K - need;
    long long best = N - max(1LL, ls - left * X) + 1;
    // 方案 B：右边少用 1 把（最后一把可能被 N 截断），左边多放 1 把
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

    // 1) 合并区间（重叠或相邻都合并）
    for (int i = 1; i <= U; i ++){
        if (m > 0 && iv[i].a <= en[m] + 1)
            en[m] = max(en[m], iv[i].b);
        else{
            m ++;
            st[m] = iv[i].a;
            en[m] = iv[i].b;
        }
    }

    // 2) 结点
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

    // 3) 空格起点的余数，排序去重
    for (int t = 0; t <= m; t ++)
        if (pos[t] >= 0)
            rs[++ nr] = pos[t] % X;
    if (nr == 0){                       // 没有空格：整片海滩都盖住了
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

    // 4) 从右往左：先算空格起点的跳转，再把 block t 画进线段树
    for (int t = m; t >= 1; t --){
        if (pos[t] >= 0)
            jump(t);
        paintBlock(t);
    }
    if (pos[0] >= 0)
        jump(0);

    // 5) dist：到达 N 最少几把伞（跳转只往右，从右往左算）
    for (int t = m; t >= 1; t --)
        if (pos[t] >= 0)
            dist[t] = cst[t] + (nxt[t] == E ? 0 : dist[nxt[t]]);
    if (pos[0] >= 0)
        dist[0] = cst[0] + (nxt[0] == E ? 0 : dist[nxt[0]]);

    // 6) 倍增表
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

    // 7) 枚举候选左端：每个 block 的起点，以及位置 1
    long long ans = 0;
    for (int t = 1; t <= m; t ++)
        ans = max(ans, value(st[t], en[t] == N ? E : t));
    if (pos[0] >= 0)
        ans = max(ans, value(1, 0));

    cout << ans << endl;
    return 0;
}
