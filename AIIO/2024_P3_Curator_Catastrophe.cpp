// AIIO 2024 P3 - Curator Catastrophe
// 方法：置换环 permutation cycles + 下界证明 lower bound + 构造 construction
//       答案 = (N - 环数) + 2 * max(ceil(B/2), 同高度坏环的最大个数)
#include <bits/stdc++.h>
using namespace std;

struct badCycle{
    int h, rep;                     // 这个坏环的高度、环上的一个点（代表）
}bad[200010];

int n, B;
int a[200010], h[200010];
bool vis[200010];
int cyc[200010], len;               // 当前正在处理的一个环
int opx[500010], opy[500010], ops;  // 记录所有交换
int cntH[200010];                   // 当前环里每种高度出现几次
int distinctH, ones;                // 当前环里不同高度的个数、恰好出现 1 次的高度个数
int pv[200010], nx[200010];         // 当前环的前驱、后继
bool alive[200010];
int cand[1000010], qh, qt;          // "可能可以删"的点的队列

bool cmp(badCycle x, badCycle y){
    return x.h < y.h;
}

void doSwap(int x, int y){          // 交换基座 x、y 上的画
    ops ++;
    opx[ops] = x;
    opy[ops] = y;
    int t = a[x];
    a[x] = a[y];
    a[y] = t;
}

// 从 s 出发找出整个环，放进 cyc[1..len]
void getCycle(int s){
    len = 0;
    int x = s;
    while (!vis[x]){
        vis[x] = true;
        cyc[++ len] = x;
        x = a[x];
    }
}

void addH(int hh, int d){           // 高度 hh 的出现次数 + d，同时维护 distinctH、ones
    if (cntH[hh] == 1)
        ones --;
    if (cntH[hh] == 0)
        distinctH ++;
    cntH[hh] += d;
    if (cntH[hh] == 1)
        ones ++;
    if (cntH[hh] == 0)
        distinctH --;
}

// 删除点 v：交换 (前驱, v)，画到达 v，v 离开环
void removeNode(int v){
    int u = pv[v], w = nx[v];
    doSwap(u, v);
    alive[v] = false;
    nx[u] = w;
    pv[w] = u;
    addH(h[v], -1);
    len --;
}

// 把一个"好环"（至少两种高度）用 len-1 次合法交换排好
void solveCycle(){
    distinctH = 0;
    ones = 0;
    for (int i = 1; i <= len; i ++){
        int x = cyc[i];
        addH(h[x], 1);
        alive[x] = true;
        nx[x] = a[x];
        pv[a[x]] = x;
    }
    int total = len;
    qh = 1;
    qt = 0;
    for (int i = 1; i <= total; i ++)
        cand[++ qt] = cyc[i];

    while (len > 1){
        if (distinctH == 2 && ones >= 1){
            // 特殊形态："独特高度"的 U + 其余全是另一种高度 -> 让 U 不断吃掉它的后继
            int U = 0;
            for (int i = 1; i <= total; i ++)
                if (alive[cyc[i]] && cntH[h[cyc[i]]] == 1){
                    U = cyc[i];
                    break;
                }
            while (len > 1)
                removeNode(nx[U]);
            break;
        }
        int v = cand[qh ++];
        if (!alive[v] || h[pv[v]] == h[v])  // 现在不能删
            continue;
        int w = nx[v];
        removeNode(v);
        cand[++ qt] = w;                    // w 的前驱变了，重新检查
    }
    for (int i = 1; i <= total; i ++)       // 清空计数，给下一个环用
        if (alive[cyc[i]]){
            addH(h[cyc[i]], -1);
            alive[cyc[i]] = false;
        }
}

int anchorFor(int H){                       // 找一个高度不是 H 的基座
    for (int i = 1; i <= n; i ++)
        if (h[i] != H)
            return i;
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    for (int i = 1; i <= n; i ++)
        cin >> h[i];

    // 1) 找所有环，数环数 C，找出坏环（长度 >= 2 且高度全相同）
    int C = 0;
    for (int i = 1; i <= n; i ++)
        if (!vis[i]){
            getCycle(i);
            C ++;
            if (len >= 2){
                bool same = true;
                for (int j = 2; j <= len; j ++)
                    if (h[cyc[j]] != h[cyc[1]])
                        same = false;
                if (same){
                    B ++;
                    bad[B].h = h[cyc[1]];
                    bad[B].rep = cyc[1];
                }
            }
        }

    bool allSame = true;
    for (int i = 2; i <= n; i ++)
        if (h[i] != h[1])
            allSame = false;
    if (B > 0 && allSame){
        cout << -1 << endl;
        return 0;
    }

    // 2) 坏环按高度排序，找出同高度最多的一组 [bs, be]
    sort(bad + 1, bad + B + 1, cmp);
    int maxb = 0, bs = 0, be = 0;
    for (int i = 1; i <= B; ){
        int j = i;
        while (j + 1 <= B && bad[j + 1].h == bad[i].h)
            j ++;
        if (j - i + 1 > maxb){
            maxb = j - i + 1;
            bs = i;
            be = j;
        }
        i = j + 1;
    }
    int merges = max((B + 1) / 2, maxb);
    long long answer = (long long)(n - C) + 2LL * merges;

    // 3) 合并 merge
    if (B > 0){
        if (2 * maxb >= B){
            // 一种高度占多数：其它坏环各配一个多数派，剩下的多数派找锚点
            int k = bs;
            for (int i = 1; i <= B; i ++)
                if (i < bs || i > be){
                    doSwap(bad[i].rep, bad[k].rep);
                    k ++;
                }
            int z = anchorFor(bad[bs].h);
            for (; k <= be; k ++)
                doSwap(bad[k].rep, z);
        }else{
            // 按高度排好后，第 i 个与第 i+half 个配对（高度一定不同）
            int half = (B + 1) / 2;
            for (int i = 1; i <= B / 2; i ++)
                doSwap(bad[i].rep, bad[i + half].rep);
            if (B % 2 == 1){
                int mid = B / 2 + 1;
                doSwap(bad[mid].rep, anchorFor(bad[mid].h));
            }
        }
    }

    // 4) 现在每个环都是好环，逐个排好
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i ++)
        if (!vis[i]){
            getCycle(i);
            if (len >= 2)
                solveCycle();
        }

    cout << answer << "\n";         // ops 必然等于 answer
    for (int i = 1; i <= ops; i ++)
        cout << opx[i] << " " << opy[i] << "\n";
    return 0;
}
