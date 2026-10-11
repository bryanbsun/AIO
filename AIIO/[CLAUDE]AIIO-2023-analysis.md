# AIIO 2023 题目分析与讲解

> AIIO = Australian Invitational Informatics Olympiad（澳大利亚信息学邀请赛），难度明显高于 AIO。
> 本文件三道题：Sculpture III、Electrical Fault、Pinnacle。所有 C++ 代码均已通过暴力对拍（brute-force stress testing）和最大数据规模计时测试。
> 代码风格与 P6 讲义一致：`#include <bits/stdc++.h>`、全局数组（下标从 1 开始）、`cin`/`cout`；不用 `vector`/`set`/`pair`/`map`、lambda、`auto`（唯一例外：Kth Number 的官方接口 `ask_host` 要求 `vector`）。堆 heap 和邻接表 adjacency list 都用数组手写。

## 本年总览

| 题目 | 核心知识点 | 学生需要的新知识 | 难度 |
|---|---|---|---|
| Sculpture III | 动态规划 DP（dynamic programming）、前缀最大值 prefix maximum、后缀最小值 suffix minimum | **DP 入门**（第一次接触 DP 的好题） | ★★★ |
| Electrical Fault | 最短路 shortest path、Dijkstra、多源 multi-source、来源标签 source label | **堆 heap**（手写小根堆）、Dijkstra | ★★★★ |
| Pinnacle | 单调栈 monotonic stack、稀疏表 sparse table（RMQ）、前缀和 prefix sum、"跳跃链"求和 | 单调栈、稀疏表 | ★★★★ |

---

## Problem 1：Sculpture III

### 题意（Problem summary）
一排 N 个基座（pedestal），第 i 个的美观分为 $a_i$。有 M 条限制（restriction），第 i 条说：区间 [$l_i$, $r_i$] 内最多只能用一个基座。选一些基座，使总分最大。N, M ≤ 100 000。

### 关键知识（Key knowledge）
- **动态规划 DP**：状态 state、转移 transition、边界 base case
- **前缀最大值 prefix maximum**：把 DP 的 “max over j < f” 变成 O(1)
- **后缀最小值 suffix minimum**：预处理每个位置受到的最强限制

### 核心洞察（Key insight）
1. **限制本质上是“两两冲突” pairwise conflict**：“区间内最多一个” ⇔ “区间内任意两个被选的基座冲突”。
2. **只需检查相邻的两个被选基座**：若被选的 j1 < j2 < i，且某个区间同时包含 j1 和 i，那它也一定包含 j2 和 i（区间是连续的）。所以只要检查“上一个被选的”和“当前这个”即可 —— 这正是 DP 需要的“无后效性”。
3. **对每个 i，合法的“上一个”恰好是一段前缀**：设 f(i) = min( i, 所有满足 r ≥ i 的限制中最小的 l )。上一个被选的 j 合法 ⇔ j < f(i)。

### 分步讲解（Step-by-step，给学生讲的顺序）

**第 1 步：从最简单的子任务开始（Subtask 3：限制都是 [i, i+1]）**
这就是经典的“打家劫舍 House Robber”：不能选相邻两个。
- 定义 `dp[i]` = 只考虑前 i 个基座、且**第 i 个被选**时的最大分。
- 转移：`dp[i] = a[i] + max(dp[1..i-2], 0)`。
- 用 `best[i] = max(dp[1..i])` 维护前缀最大值，转移变成 O(1)。
- 这是向学生介绍 DP 三要素的最好例子：**状态**（dp[i] 的含义）、**转移**（dp[i] 从哪里来）、**答案**（best[N]）。

**第 2 步：推广到任意区间**
- 问：如果选了 i，上一个被选的 j 最大可以是多少？
- 所有“覆盖到 i 的右边”（r ≥ i）的限制里，若 l ≤ j，则 j 和 i 同在一个区间里 → 冲突。
- 所以 j 必须小于所有这些 l 的最小值：`j < min{ l : r ≥ i }`，再和 i 取 min（j 本来就 < i）。

**第 3 步：怎样快速求 min{ l : r ≥ i }？**
- 先把每条限制记到右端点上：`lim[r] = min(lim[r], l)`。
- 再从右往左做**后缀最小值**：`lim[i] = min(lim[i], lim[i+1])`。

**第 4 步：写出完整 DP**
```
f      = min(i, lim[i])
dp[i]  = a[i] + best[f - 1]      // best[0] = 0 表示前面一个都没选
best[i]= max(best[i-1], dp[i])
答案   = best[N]
```

**第 5 步：用样例 1 手算验证**（强烈建议带学生在白板上画一遍）

### 子任务阶梯（Subtask ladder）
| 子任务 | 思路 |
|---|---|
| 1（$a_i$ = 1，小数据） | 贪心 greedy：从左往右，能选就选（区间调度 interval scheduling 的变体） |
| 2（$a_i$ = 1） | 同上，配合后缀最小值加速 |
| 3（相邻限制） | House Robber DP |
| 4（N, M ≤ 1000） | DP，转移时 O(N) 暴力找合法的 j |
| 5 | 本文解法 O(N + M) |

### 复杂度（Complexity）
时间 O(N + M)，空间 O(N)。

### 常见错误（Common pitfalls）
- 忘记“一个都不选”也是合法的前驱 → `best[0] = 0`。
- 以为要检查所有被选的基座两两之间 → 其实只需要相邻的（洞察 2）。

### C++ 代码
```cpp
// AIIO 2023 P1 - Sculpture III
// 方法：DP（dp[i] = 最后一个用的基座是 i）+ 后缀最小值 suffix min + 前缀最大值 prefix max
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long a[100010];
int lim[100010];                // lim[i] = 所有右端点 r >= i 的限制中，最小的左端点 l
long long dp[100010];           // dp[i]：最后一个使用的基座恰好是 i 时的最大美观度
long long best[100010];         // best[i] = max(dp[1..i])，best[0] = 0 表示一个都不选

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];

    // 1) 把每条限制记到右端点上
    for (int i = 1; i <= n + 1; i ++)
        lim[i] = n + 1;
    for (int k = 1; k <= m; k ++){
        int l, r;
        cin >> l >> r;
        lim[r] = min(lim[r], l);
    }

    // 2) 后缀最小值：lim[i] = min(lim[i], lim[i+1])
    for (int i = n - 1; i >= 1; i --)
        lim[i] = min(lim[i], lim[i + 1]);

    // 3) DP：选了 i，上一个被选的 j 必须满足 j < f = min(i, lim[i])
    best[0] = 0;
    for (int i = 1; i <= n; i ++){
        int f = min(i, lim[i]);
        dp[i] = a[i] + best[f - 1];
        best[i] = max(best[i - 1], dp[i]);
    }

    cout << best[n] << endl;
    return 0;
}
```

---

## Problem 2：Electrical Fault

### 题意
V 个端子（terminal）、E 条带权无向边（wire），其中 K 个是接地端子（grounded terminal）。求**两个不同的接地端子之间**的最短路径长度。V ≤ 10^5，E ≤ 3×10^5。

### 关键知识
- **最短路 shortest path**：边权相同时用 BFS，边权不同用 **Dijkstra**
- **堆 heap**（学生的新知识，这里是很自然的引入场景）：代码用数组手写小根堆 min-heap
- **邻接表 adjacency list**：用数组实现的“链式前向星”（`head` / `nxt` / `to` / `wt`）
- **多源最短路 multi-source shortest path**：把所有源点距离同时设为 0 放进队列
- **来源标签 source label / owner**

### 核心洞察
1. 对每个点 v，求 `dist[v]` = 到**最近**接地端子的距离，以及 `owner[v]` = 那个最近的接地端子是谁。一次多源 Dijkstra 就能同时得到两者。
2. **最优路径上必有一条“边界边”**：考虑两个接地端子 s ≠ t 之间的最短路。沿着路径走，owner 从 s（起点 owner 是 s）变到 t（终点 owner 是 t），中间一定有一条边 (u, v) 两端 owner 不同。而 `dist[u] + w + dist[v]` 就是一条从 owner[u] 到 owner[v] 的路径长度，且不超过原路径长度。
3. 所以：**答案 = min over 所有边 (u, v, w) 且 owner[u] ≠ owner[v] 的 dist[u] + w + dist[v]**。

### 分步讲解

**第 1 步：K = 2 且边权为 1（Subtask 1）**
直接从 $x_1$ 做 BFS，答案是 dist[$x_2$]。

**第 2 步：K = 2，边权任意（Subtask 2）→ 引入 Dijkstra**
- 讲清楚 Dijkstra 的贪心本质：每次取出“当前距离最小、还没确定”的点，它的距离就确定了。
- “每次取最小” → 需要一个能快速取最小值的数据结构 → **堆 heap**。
- 手写小根堆（完全二叉树存在数组里，节点 i 的孩子是 2i、2i+1）：`push` 把新元素放到末尾再**上浮 sift up**；`pop` 把末尾元素挪到堆顶再**下沉 sift down**。两者都是 O(log n)。
- （比赛时也可以直接用 STL 的 `priority_queue`，原理完全相同；课程示例坚持用数组，方便学生看清每一步。）
- 讲“懒惰删除 lazy deletion”：同一个点可能多次入堆，取出时若 `d > dist[u]` 就跳过。

**第 3 步：K 很大时，朴素做法为什么不行？**
- 从每个接地端子各跑一次 Dijkstra → O(K · E log V)，K 可以到 10^5，太慢。

**第 4 步：多源 + 来源标签**
- 所有接地端子同时作为起点（dist = 0，owner = 自己）。
- 松弛时 `owner[v] = owner[u]`。
- 这样每个点知道“离我最近的是谁”，但我们要的是**两个不同**端子之间的路径 → 洞察 2：枚举边界边。

**第 5 步：为什么枚举边界边一定不会漏？**（带学生做这个证明，这是本题精华）
- 取最优路径 s = p0, p1, …, pk = t。owner[p0] = s，owner[pk] = t，s ≠ t，所以某个相邻对 ($p_i$, $p_{i+1}$) 的 owner 不同。
- $\mathrm{dist}[p_i] \le  \text{路径上 } s \text{ 到 } p_i \text{ 的长度}$，$\mathrm{dist}[p_{i+1}] \le  \text{路径上 } p_{i+1} \text{ 到 } t \text{ 的长度}$。
- 所以这条边给出的候选值 ≤ 最优答案。又因为候选值本身对应一条真实的、连接两个不同接地端子的路径，所以不会比最优答案更小。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（K = 2，边权 1） | BFS |
| 2（K = 2） | Dijkstra |
| 3（边权 1） | 多源 BFS + owner + 枚举边 |
| 4 | 多源 Dijkstra + owner + 枚举边，O(E log V) |

### 常见错误
- 答案可能超过 int 吗？V·d ≤ 10^9 左右，用 long long 更保险。
- 两个接地端子直接相连的边，也要被枚举到（我们的做法自然包含）。
- 重边（两条边连同一对点）不影响正确性。

### C++ 代码
```cpp
// AIIO 2023 P2 - Electrical Fault
// 方法：多源 Dijkstra（multi-source，手写小根堆 heap）+ 来源标签 owner + 枚举"边界边"
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int V, E, K;
int ea[300010], eb[300010], ew[300010];         // 所有的边
int head[100010], nxt[600010], to[600010], wt[600010], cnt;   // 邻接表（链式前向星）
long long dist[100010];         // dist[v]：v 到最近接地端子的距离
int owner[100010];              // owner[v]：离 v 最近的接地端子是谁

// 手写小根堆：按 hd[] 从小到大，堆里存 (距离, 点)
long long hd[1000010];
int hv[1000010], hs;

void push(long long d, int v){
    hs ++;
    int i = hs;
    while (i > 1 && hd[i / 2] > d){             // 往上浮
        hd[i] = hd[i / 2];
        hv[i] = hv[i / 2];
        i /= 2;
    }
    hd[i] = d;
    hv[i] = v;
}

void pop(){                                     // 删掉堆顶
    long long d = hd[hs];
    int v = hv[hs];
    hs --;
    int i = 1;
    while (2 * i <= hs){                        // 往下沉
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

void addEdge(int u, int v, int w){
    cnt ++;
    to[cnt] = v;
    wt[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> V >> E >> K;
    for (int i = 1; i <= V; i ++){
        dist[i] = INF;
        owner[i] = 0;
    }
    for (int i = 1; i <= K; i ++){
        int x;
        cin >> x;
        dist[x] = 0;                            // 所有接地端子同时作为起点
        owner[x] = x;
        push(0, x);
    }
    for (int i = 1; i <= E; i ++){
        cin >> ea[i] >> eb[i] >> ew[i];
        addEdge(ea[i], eb[i], ew[i]);
        addEdge(eb[i], ea[i], ew[i]);
    }

    // 1) 多源 Dijkstra
    while (hs > 0){
        long long d = hd[1];
        int u = hv[1];
        pop();
        if (d > dist[u])                        // 过期的记录，跳过
            continue;
        for (int e = head[u]; e; e = nxt[e]){
            int v = to[e];
            if (d + wt[e] < dist[v]){
                dist[v] = d + wt[e];
                owner[v] = owner[u];            // 继承来源
                push(dist[v], v);
            }
        }
    }

    // 2) 枚举每条边：两端来源不同，就连起了两个不同的接地端子
    long long ans = INF;
    for (int i = 1; i <= E; i ++){
        int u = ea[i], v = eb[i];
        if (owner[u] != 0 && owner[v] != 0 && owner[u] != owner[v])
            ans = min(ans, dist[u] + ew[i] + dist[v]);
    }

    cout << ans << endl;
    return 0;
}
```

---

## Problem 3：Pinnacle

### 题意
N 座方块塔，高度 $a_i$。“山形 mountain”：可以分成左右两半，左半非递减（non-decreasing），右半非递增（non-increasing）。Q 次询问，每次问把区间 [l, r] 变成山形至少要**加**多少方块（不能删）。N, Q ≤ 100 000，$a_i$ ≤ 10^9。

### 关键知识
- **前缀和 prefix sum**
- **单调栈 monotonic stack**：求“下一个更大元素 next greater element”
- **稀疏表 sparse table**：O(1) 区间最值查询 RMQ（range maximum query）
- **long long**：答案可达 10^14

### 核心洞察
1. **最优山峰就在区间最大值处**：最终每座塔的高度至少是 `min(左边最高, 右边最高)`（包括自己）。而“左边部分补成前缀最大值、右边部分补成后缀最大值、在最高塔处汇合”恰好达到这个下界。
   所以：答案 = $\sum_{i=l}^{m} (\mathrm{pmax}_i - a_i) + \sum_{i=m}^{r} (\mathrm{smax}_i - a_i)$，其中 m 是 [l, r] 中最高塔的位置，$\mathrm{pmax}_i$ 是从 l 到 i 的前缀最大值，$\mathrm{smax}_i$ 是从 i 到 r 的后缀最大值。
2. **前缀最大值是一个“阶梯函数 step function”**：从 l 出发，前缀最大值只在“破纪录 record”的位置变化：l → nx[l] → nx[nx[l]] → …，nx[i] 是 i 右边第一个 ≥ a[i] 的位置。每一段贡献 `a[x] × (nx[x] − x)`。
3. **“跳跃链”上的后缀和可以预处理**：`SL[i] = a[i] × (nx[i] − i) + SL[nx[i]]`。因为 m 是区间最大值，从 l 出发的链**一定经过 m**，所以
   `Σ_{i=l..m} 前缀最大值 = SL[l] − SL[m] + a[m]`（链在 m 处截断，m 本身贡献 a[m]）。
   右边同理（向左找第一个**严格**更大的，SR 数组）。

### 分步讲解

**第 1 步：只有一个询问（Subtask 1）怎么做？**
- 找到最大值位置 m；从左往右扫到 m，维护当前最大值 cur，累加 `cur − a[i]`；从右往左同理。O(N)。
- 让学生先证明“山峰放在最大值处最优”：画图，任何山形里最高那座塔两边都得“爬上去/爬下来”。

**第 2 步：很多询问，暴力 O(NQ) 太慢，瓶颈在哪？**
- 瓶颈是“从 l 到 m 的前缀最大值之和”。画出 a 的柱状图，从 l 往右，前缀最大值像台阶一样上升 —— 台阶的拐点就是“下一个 ≥ 当前值”的位置。

**第 3 步：单调栈求 nx[i]**（先单独讲单调栈，这是新知识）
- 从右往左扫，栈里保存“候选的更高塔”；弹出所有比 a[i] 矮的，栈顶就是 nx[i]。每个元素进出栈各一次 → O(N)。

**第 4 步：链上求和的“差分”技巧**
- 类比前缀和：`sum(l..r) = pre[r] − pre[l−1]`。这里是“沿着链”的后缀和，`SL[l] − SL[m]` 就是链上从 l 到 m 之前的所有台阶贡献。
- 关键：为什么链一定经过 m？因为 m 比 [l, r] 中所有塔都不矮，链上每一步都不会“跳过” m。
- **细节**：若最大值出现多次，左边用 “≥” 的链会停在**最后一个**最大值；右边用 “>” 的链也停在**最后一个**最大值。两边在同一个 m 汇合 —— 所以稀疏表要返回“最靠右的最大值位置”。

**第 5 步：稀疏表 RMQ**（新知识）
- `sp[k][i]` = 区间 [i, i + 2^k − 1] 的最大值位置。查询时用两个长度为 2^k 的区间覆盖 [l, r]。O(N log N) 预处理，O(1) 查询。

**第 6 步：组装答案**
`答案 = (SL[l] − SL[m] + a[m]) + (SR[r] − SR[m] + a[m]) − a[m] − (pre[r] − pre[l−1])`

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（一次询问） | O(N) 扫描 |
| 2（l = 1 且 $a_1$ = 10^9） | 最高塔永远是第 1 座，只需计算“右半部分补成非递增”的代价；r 每次加一，用单调栈增量维护后缀最大值之和 |
| 3（l = 1，r = 1..N） | 询问是逐渐变长的前缀；可以增量维护，也可以直接用满分做法 |
| 4（$a_i$ ≤ 10） | 按“高度层 layer”思考：第 h 层需要补的方块数 = [l, r] 中第一个和最后一个高度 ≥ h 的位置之间、高度 < h 的塔数。对每个 h 预处理前缀计数即可 O(10) 回答 |
| 5 | 单调栈 + 链上求和 + 稀疏表，O((N + Q) log N) |

### 常见错误
- 用 int 存答案 → 溢出，必须 long long。
- 最大值重复时，左右两边的链停在不同位置 → 必须统一用“最后一个最大值”，并且左用 ≥、右用 >。
- 汇合点 m 被左右各算一次，要减一次 a[m]。

### C++ 代码
```cpp
// AIIO 2023 P3 - Pinnacle
// 方法：山峰放在区间最大值处 + 单调栈 monotonic stack（找下一个更大）
//       + "跳跃链"上的后缀和 + 稀疏表 Sparse Table（区间最大值位置）+ Prefix Sum
#include <bits/stdc++.h>
using namespace std;

int n, q;
long long a[100010], pre[100010];
int nx[100010], pv[100010];         // nx[i]：右边第一个 >= a[i] 的位置；pv[i]：左边第一个 > a[i] 的位置
long long SL[100010], SR[100010];   // 沿链的和：SL 向右（前缀最大值之和），SR 向左（后缀最大值之和）
int st[100010], top;                // 单调栈
int sp[18][100010], lg[100010];     // 稀疏表：sp[k][i] = [i, i+2^k-1] 中最大值的位置

// 两个位置中值更大的；相等时取更靠右的
int better(int i, int j){
    if (a[i] != a[j]){
        if (a[i] > a[j])
            return i;
        return j;
    }
    return max(i, j);
}

int queryMaxPos(int l, int r){
    int k = lg[r - l + 1];
    return better(sp[k][l], sp[k][r - (1 << k) + 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q;
    pre[0] = 0;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    // 1) 单调栈：从右往左求 nx[]（第一个 >=），从左往右求 pv[]（第一个 >）
    top = 0;
    for (int i = n; i >= 1; i --){
        while (top > 0 && a[st[top]] < a[i])
            top --;
        if (top > 0)
            nx[i] = st[top];
        else
            nx[i] = n + 1;
        st[++ top] = i;
    }
    top = 0;
    for (int i = 1; i <= n; i ++){
        while (top > 0 && a[st[top]] <= a[i])
            top --;
        if (top > 0)
            pv[i] = st[top];
        else
            pv[i] = 0;
        st[++ top] = i;
    }

    // 2) 沿链的后缀和：每一段"台阶"贡献 a[x] * 长度
    SL[n + 1] = 0;
    for (int i = n; i >= 1; i --)
        SL[i] = a[i] * (nx[i] - i) + SL[nx[i]];
    SR[0] = 0;
    for (int i = 1; i <= n; i ++)
        SR[i] = a[i] * (i - pv[i]) + SR[pv[i]];

    // 3) 稀疏表
    lg[1] = 0;
    for (int i = 2; i <= n; i ++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i ++)
        sp[0][i] = i;
    for (int k = 1; (1 << k) <= n; k ++)
        for (int i = 1; i + (1 << k) - 1 <= n; i ++)
            sp[k][i] = better(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);

    // 4) 回答询问
    for (int t = 1; t <= q; t ++){
        int l, r;
        cin >> l >> r;
        int m = queryMaxPos(l, r);                  // 最高塔（最靠右的那个）
        long long leftSum = SL[l] - SL[m] + a[m];   // sum_{i=l..m} max(a[l..i])
        long long rightSum = SR[r] - SR[m] + a[m];  // sum_{i=m..r} max(a[i..r])
        long long ans = leftSum + rightSum - a[m] - (pre[r] - pre[l - 1]);   // m 被算了两次
        cout << ans << "\n";
    }
    return 0;
}
```
