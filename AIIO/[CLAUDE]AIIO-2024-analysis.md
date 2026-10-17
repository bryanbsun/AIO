# AIIO 2024 题目分析与讲解

> 本文件三道题：Speed Friending、Overcycle、Curator Catastrophe。所有 C++ 代码均已通过暴力对拍（brute-force stress testing）和最大数据规模计时测试。
> 代码风格与 P6 讲义一致：`#include <bits/stdc++.h>`、全局数组（下标从 1 开始）、`cin`/`cout`；不用 `vector`/`set`/`pair`/`map`、lambda、`auto`（唯一例外：Kth Number 的官方接口 `ask_host` 要求 `vector`）。堆 heap 和邻接表 adjacency list 都用数组手写。

## 本年总览

| 题目 | 核心知识点 | 学生需要的新知识 | 难度 |
|---|---|---|---|
| Speed Friending | 观察/证明（"归并两个序列"模型）、区间最值、线段树 segment tree | 线段树（单点修改 + 区间查询） | ★★★ |
| Overcycle | 最短路 Dijkstra、图的结构分析、前缀和 | 堆 heap / Dijkstra（与 2023 Electrical Fault 呼应） | ★★★ |
| Curator Catastrophe | 置换环 permutation cycles、下界证明 lower bound、构造 construction | 置换环分解；"证明下界 + 构造达到下界"的思维方式 | ★★★★★ |

---

## Problem 1：Speed Friending

### 题意
N 个学生排成一行，性格值 $p_i$ 互不相同。学生 s 发起"速配"：每次在左边最近的 l 和右边最近的 r 中，选性格值与 $p_s$ 更接近的一个交朋友（平局可任选），被选者离开队伍，直到所有人都成了朋友。问"最后一个朋友 final friend"是谁（若不唯一输出 −1）。还有修改操作：改变某个 $p_s$。N, Q ≤ 200 000。

### 关键知识
- **观察与证明**：把复杂过程化简成一个简单判定
- **区间最大值/最小值 range max/min**
- **线段树 segment tree**：支持单点修改 point update + 区间查询 range query

### 核心洞察
1. **最后一个朋友只能是学生 1 或学生 N**：队伍从 s 向两边扩张，某一边先"吃完"，最后一个必然是另一边的最末端。
   问题变成：**左边先吃完，还是右边先吃完？**
2. 设 $d_i$ = |$p_i$ − $p_s$|。过程等价于**归并 merge 两个序列**：左序列 $d_{s-1}$, $d_{s-2}$, …, $d_1$；右序列 $d_{s+1}$, …, $d_N$；每次比较两个队首，取较小的。
3. **只看两边的最大值**：设 maxL = 左边最大的 d，maxR = 右边最大的 d。
   - 若 maxL < maxR：右边那个"最大值元素"一旦成为右队首，就会卡住右边；此时左边所有元素都 < maxR，会被先取完 → 左边先吃完 → **最后一个是 N**。
   - 若 maxL > maxR：对称，**最后一个是 1**。
   - 若 maxL = maxR：两边都会被各自的最大值卡住，此时两个队首相等，可以任选；之后可以一直选同一边直到吃完 → 两种结局都可能 → **−1**。
4. 边界：s = 1 时左边为空，答案是 N；s = N 时答案是 1。

### 分步讲解

**第 1 步：先让学生手动模拟题目中的例子**，并问："最后一个朋友可能是中间的人吗？"——引出洞察 1。

**第 2 步：Subtask 1（$p_s$ = 0）**
- 此时 $d_i$ = $p_i$，"左边的最大距离"就是左边的最大 p 值。
- 让学生猜想：只要比较 max(左边) 和 max(右边)。用几个例子验证。

**第 3 步：证明猜想（洞察 3）**
- 画出两个序列，标出各自的最大值位置。关键句："一个队首是最大值时，它会一直站着不动，直到另一边的所有更小的元素都被取走。"

**第 4 步：一般的 $p_s$**
- 左边最大距离 = max( 左边最大 p − $p_s$, $p_s$ − 左边最小 p )。因为 |x − $p_s$| 的最大值一定在 x 最大或 x 最小处取到。
- 所以只需要**前缀的最大/最小值**和**后缀的最大/最小值**。

**第 5 步：没有修改（Subtask 3）**：预处理前缀 max/min、后缀 max/min 数组，每次 O(1)。

**第 6 步：有修改（Subtask 4）→ 线段树**（新知识）
- 前缀数组在单点修改后要 O(N) 重算，太慢。
- 线段树每个节点存区间 max 和 min；修改和查询都是 O(log N)。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（一次询问，$p_s$ = 0） | 比较左右最大值 |
| 2（一次询问） | O(N) 求左右最大距离 |
| 3（无修改） | 前缀/后缀 max/min 数组 |
| 4 | 线段树，O((N + Q) log N) |

### 常见错误
- 忘记 s = 1 或 s = N 的边界。
- 平局时直接输出某一端 → 应输出 −1。
- 性格值到 10^9，差值计算用 long long 更稳妥。

### C++ 代码
```cpp
// AIIO 2024 P1 - Speed Friending
// 方法：关键观察（最后一个朋友只能是 1 或 N，只需比较左右两边的"最大性格距离"）
//       + 线段树 Segment Tree（单点修改、区间最大值/最小值）
#include <bits/stdc++.h>
using namespace std;

int n, q;
long long p[200010];
long long mx[800010], mn[800010];   // 线段树：节点存区间最大值、最小值
long long qmx, qmn;                 // 一次查询的结果

void update(int node, int l, int r, int pos, long long val){
    if (l == r){
        mx[node] = val;
        mn[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * node, l, mid, pos, val);
    else
        update(2 * node + 1, mid + 1, r, pos, val);
    mx[node] = max(mx[2 * node], mx[2 * node + 1]);
    mn[node] = min(mn[2 * node], mn[2 * node + 1]);
}

// 查询 [ql, qr] 的最大值、最小值，结果放在 qmx、qmn
void query(int node, int l, int r, int ql, int qr){
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr){
        qmx = max(qmx, mx[node]);
        qmn = min(qmn, mn[node]);
        return;
    }
    int mid = (l + r) / 2;
    query(2 * node, l, mid, ql, qr);
    query(2 * node + 1, mid + 1, r, ql, qr);
}

// [l, r] 里所有人与学生 s 的最大性格距离
long long maxDist(int l, int r, int s){
    qmx = -1;
    qmn = 2000000000;
    query(1, 1, n, l, r);
    return max(qmx - p[s], p[s] - qmn);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> p[i];
        update(1, 1, n, i, p[i]);
    }
    cin >> q;
    for (int k = 1; k <= q; k ++){
        int t, s;
        cin >> t >> s;
        if (t == 2){
            long long x;
            cin >> x;
            p[s] = x;
            update(1, 1, n, s, x);
            continue;
        }
        if (s == 1){                    // 左边没人：最后一个一定是 N
            cout << n << "\n";
            continue;
        }
        if (s == n){                    // 右边没人：最后一个一定是 1
            cout << 1 << "\n";
            continue;
        }
        long long L = maxDist(1, s - 1, s);
        long long R = maxDist(s + 1, n, s);
        if (L < R)                      // 左边先被吃完 -> 最后是 N
            cout << n << "\n";
        else if (L > R)                 // 右边先被吃完 -> 最后是 1
            cout << 1 << "\n";
        else                            // 平局：两种结局都可能
            cout << -1 << "\n";
    }
    return 0;
}
```

---

## Problem 2：Overcycle

### 题意
N 个郊区排成一条线，第 i 条路连接 i 和 i+1，耗时 $d_i$。另有 A 条"捷径 Overcycle"连接郊区 1 与 $x_i$（耗时 $k_i$），B 条捷径连接郊区 N 与 $y_i$（耗时 $l_i$）。Q 次询问 s < t 的最短路。N, Q ≤ 200 000，权值 ≤ 10^9。

### 关键知识
- **前缀和 prefix sum**：沿路的距离 pre[t] − pre[s]
- **Dijkstra 最短路** + **手写小根堆 heap**（与 2023 Electrical Fault 同一份模板）
- **图结构分析**：所有捷径都经过 1 或 N

### 核心洞察
1. **任何路径要么完全不用捷径，要么经过郊区 1 或郊区 N**（因为每条捷径的一端都是 1 或 N）。
2. 不用捷径时，只能在一条直线上走，最短就是 `pre[t] − pre[s]`。
3. 经过 1 的最短路 = `dist(s, 1) + dist(1, t)`，其中 dist 是**全图**最短路（允许用任何捷径）。经过 N 同理。
4. 所以只需两次 Dijkstra：从 1 出发得到 d1[]，从 N 出发得到dN[]。
   `答案 = min( pre[t] − pre[s],  d1[s] + d1[t],  dN[s] + dN[t] )`

### 分步讲解

**第 1 步：Subtask 1（没有捷径）**：前缀和，O(1) 回答。

**第 2 步：Subtask 2（小数据）**：每个询问跑一次 Dijkstra。让学生先写出这个版本，作为之后的对拍程序。

**第 3 步：引导观察**："捷径长什么样？" 画图：所有捷径像两把扇子，一把以 1 为中心，一把以 N 为中心。
→ "一条用到捷径的路径，必然在某个时刻站在 1 或 N 上。"

**第 4 步：把路径在 1（或 N）处切成两半**
- 前半段 s → 1 的最短长度就是 d1[s]（无向图，dist(s,1) = dist(1,s)）。
- 后半段 1 → t 的最短长度就是 d1[t]。
- 反过来，d1[s] + d1[t] 对应一条真实存在的路径，所以不会比真实答案小。

**第 5 步：三种情况取最小值**，完成。

**第 6 步（拓展讨论）**：Subtask 5（所有权值为 1）可以用 BFS 代替 Dijkstra。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（无捷径） | 前缀和 |
| 2（小数据） | 每次询问一次 Dijkstra |
| 3, 4（B = 0） | 只需 d1[]，也可以不用 Dijkstra：d1[v] 的计算是一维的 |
| 5（权值都为 1） | BFS |
| 6 | 两次 Dijkstra，O((N + A + B) log N + Q) |

### 常见错误
- 距离可达 2×10^14，必须 long long。
- 忘记"只走路"这一种情况（s 和 t 很近时往往最优）。

### C++ 代码
```cpp
// AIIO 2024 P2 - Overcycle
// 方法：关键观察（用到捷径的路径一定经过 1 或 N）+ 两次 Dijkstra（手写小根堆）+ Prefix Sum
//       答案 = min(只走路, d1[s] + d1[t], dN[s] + dN[t])
#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

int n, A, B, q;
long long pre[200010];              // pre[i]：沿路从 1 走到 i 的距离
int head[200010], nxt[800010], to[800010], cnt;     // 邻接表（链式前向星）
long long wt[800010];
long long d1[200010], dN[200010];

// 手写小根堆
long long hd[2000010];
int hv[2000010], hs;

void push(long long d, int v){
    hs ++;
    int i = hs;
    while (i > 1 && hd[i / 2] > d){
        hd[i] = hd[i / 2];
        hv[i] = hv[i / 2];
        i /= 2;
    }
    hd[i] = d;
    hv[i] = v;
}

void pop(){
    long long d = hd[hs];
    int v = hv[hs];
    hs --;
    int i = 1;
    while (2 * i <= hs){
        int c = 2 * i;
        if (c + 1 <= hs && hd[c + 1] < hd[c])
            c ++;
        if (hd[c] >= d)
            break;
        hd[i] = hd[c];
        hv[i] = hv[c];
        i = c;
    }
    hd[i] = d;
    hv[i] = v;
}

void addEdge(int u, int v, long long w){
    cnt ++;
    to[cnt] = v;
    wt[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

// 从 src 出发的最短路，结果写进 dist[]
void dijkstra(int src, long long dist[]){
    for (int i = 1; i <= n; i ++)
        dist[i] = INF;
    dist[src] = 0;
    hs = 0;
    push(0, src);
    while (hs > 0){
        long long d = hd[1];
        int u = hv[1];
        pop();
        if (d > dist[u])
            continue;
        for (int e = head[u]; e; e = nxt[e])
            if (d + wt[e] < dist[to[e]]){
                dist[to[e]] = d + wt[e];
                push(dist[to[e]], to[e]);
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    pre[1] = 0;
    for (int i = 1; i < n; i ++){
        long long d;
        cin >> d;
        pre[i + 1] = pre[i] + d;
        addEdge(i, i + 1, d);
        addEdge(i + 1, i, d);
    }
    cin >> A;
    for (int i = 1; i <= A; i ++){
        int x;
        long long k;
        cin >> x >> k;
        addEdge(1, x, k);
        addEdge(x, 1, k);
    }
    cin >> B;
    for (int i = 1; i <= B; i ++){
        int y;
        long long l;
        cin >> y >> l;
        addEdge(n, y, l);
        addEdge(y, n, l);
    }

    dijkstra(1, d1);                // 全图中 1 到每个点的最短路
    dijkstra(n, dN);                // 全图中 N 到每个点的最短路

    cin >> q;
    for (int k = 1; k <= q; k ++){
        int s, t;
        cin >> s >> t;
        long long ans = pre[t] - pre[s];        // 情况 1：只走路
        ans = min(ans, d1[s] + d1[t]);          // 情况 2：经过 1
        ans = min(ans, dN[s] + dN[t]);          // 情况 3：经过 N
        cout << ans << "\n";
    }
    return 0;
}
```

---

## Problem 3：Curator Catastrophe

### 题意
N 个基座，基座 i 上的画应该移到基座 $a_i$（a 是一个排列 permutation）。每次可以交换两个基座上的画，但**两个基座高度必须不同**。求最少交换次数并输出方案；不可能则输出 −1。只输出正确的次数可得 50%。N ≤ 200 000。

### 关键知识
- **置换环分解 cycle decomposition**：排列可以分解成若干个环
- 经典结论：无限制时，最少交换次数 = N − (环的个数 C)
- **每次交换使环数恰好 +1（拆分 split）或 −1（合并 merge）**
- **下界证明 lower bound + 构造 construction**

### 核心洞察
1. 把环分成三类：
   - 长度 1 的环（已经在正确位置）
   - **好环 good cycle**：长度 ≥ 2，且包含至少两种高度
   - **坏环 bad cycle**：长度 ≥ 2，且所有基座高度相同 —— 环内部任何交换都不合法！
2. **好环一定能用 (长度 − 1) 次合法交换排好**（见下面的构造）。
3. **坏环必须先和别的环合并**。设合并次数为 G，每次合并使环数 −1，之后要多拆一次，所以
   **总次数 = (N − C) + 2G**。目标：最小化 G。
4. **G 的下界**：设坏环总数为 B，高度为 h 的坏环有 $b_h$ 个。
   - 一次合并最多"救"两个坏环 → G ≥ ⌈B / 2⌉
   - 一次合并交换的是两个**不同高度**的基座，所以最多救一个高度为 h 的坏环 → G ≥ max $b_h$
   - **G = max(⌈B/2⌉, $\max_h b_h$)**，并且可以构造达到。
5. **不可能的情况**：存在坏环，且所有基座高度都相同（没有任何合法交换）。

### 分步讲解

**第 1 步：复习置换环（Subtask 1, 2：高度互不相同，所有交换都合法）**
- 从 i 出发走 i → $a_i$ → $a_{a_i}$ → … 回到 i，就是一个环。
- 每次"把一幅画送到它该去的位置"让环长 −1、环数 +1。答案 N − C。
- 让学生用样例 1 画环。

**第 2 步：高度限制带来什么新问题？**
- 举例：环 (1 2)，两个基座同高 → 环内无法交换 → 必须"借"外面的基座。
- 引出好环/坏环的分类。

**第 3 步：证明"每次交换使环数 ±1"**
- 同环内两点交换 → 环一分为二；不同环的两点交换 → 两环合二为一。
- 所以从 C 个环到 N 个环（全部归位），拆分次数 − 合并次数 = N − C → 总次数 = N − C + 2G。

**第 4 步：好环的构造（每次"送走一个"）**
- 操作："交换 u 和 $a_u$"会把 u 上的画送到 $a_u$，$a_u$ 离开环。合法条件：h[u] ≠ h[$a_u$]，即**被删节点与它的前驱高度不同**。
- 规则：只要删完之后剩下的环仍是"好环"就行。唯一危险的形态是"一个独特高度的 U + 其余全是同一高度"：此时让 U 不停地吃掉它的后继（后继高度一定 ≠ U）。
- 其它情况下，删任何"与前驱高度不同"的节点都安全（因为剩下的仍至少有两种高度）。

**第 5 步：坏环的合并策略**
- 若某种高度的坏环占多数（2·max $b_h$ ≥ B）：其它坏环各配一个多数派坏环合并；剩下的多数派坏环各自和一个"不同高度的锚点 anchor 基座"合并。共 max $b_h$ 次。
- 否则：把坏环按高度分组排成一列，第 i 个与第 i + ⌈B/2⌉ 个配对（因为每组大小 < ⌈B/2⌉，配对的两个一定高度不同）；B 为奇数时剩下一个和锚点合并。共 ⌈B/2⌉ 次。
- 合并之后所有环都是好环，再按第 4 步逐个排好。

**第 6 步：下界证明**（这一步是培养"竞赛思维"的关键，建议详细讲）
- 一个坏环在第一次被合并之前，环内无法做任何交换 → 每个坏环都必须参与至少一次合并。
- 一次合并交换两个不同高度的基座 → 最多涉及两个坏环，且它们高度不同。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1, 2（$h_i$ = i） | 所有交换合法，N − C |
| 3（只有基座 1 是矮的） | 每次交换都必须用到基座 1；答案仍可用通用公式 |
| 4（h ≤ 2，一个大环） | 练习构造：好环的排序方法 |
| 5（h ≤ 2） | 通用公式，两种高度 |
| 6, 7 | 通用做法：坏环按高度排序分组，O(N log N) |

### 常见错误
- 只数"坏环个数"而不考虑高度 → 同高度的两个坏环不能直接合并。
- 好环的拆分顺序不当，剩下"同高度"的环 → 死局。
- 输出量很大（约 2×10^5 行）：用 `ios::sync_with_stdio(false)`，换行用 `"\n"` 而不是 `endl`（`endl` 每次都会刷新缓冲区，很慢）。

### C++ 代码
```cpp
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
```
