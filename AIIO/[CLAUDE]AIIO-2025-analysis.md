# AIIO 2025 题目分析与讲解

> 本文件四道题：Buildings、Retail Empire、Amazing Game II、Kth Number（交互题 interactive）。所有 C++ 代码均已通过暴力对拍（brute-force stress testing）和最大数据规模计时测试；Kth Number 另用自写评测器对 N ≤ 8 的所有排列穷举验证（正确性 + 询问次数 ≤ ⌈N/2⌉+1）。
> 代码风格与 P6 讲义一致：`#include <bits/stdc++.h>`、全局数组（下标从 1 开始）、`cin`/`cout`；不用 `vector`/`set`/`pair`/`map`、lambda、`auto`（唯一例外：Kth Number 的官方接口 `ask_host` 要求 `vector`）。堆 heap 和邻接表 adjacency list 都用数组手写。

## 本年总览

| 题目 | 核心知识点 | 学生需要的新知识 | 难度 |
|---|---|---|---|
| Buildings | 计数数组 counting array、滑动"已见集合" | 无 | ★★ |
| Retail Empire | 贪心 greedy + 支配性证明、**0/1 背包 0/1 knapsack** | **DP：0/1 背包** | ★★★ |
| Amazing Game II | BFS、全源最短路、**贪心交换论证 exchange argument**、双指针 two pointers、倒推计数 | 把"游戏"转化成"时间点序列"的建模能力 | ★★★★★ |
| Kth Number | 交互题 interactive、分类讨论 case analysis、排名 rank 推理 | 交互题格式；"对手 adversary"思维 | ★★★★★ |

---

## Problem 1：Buildings

### 题意
N 栋楼，高度 $H_i$。若 |i − j| ≥ K 称两栋楼"相距够远 far apart"。问是否存在两栋相距够远、高度差恰好为 X 的楼。N ≤ 200 000，$H_i$ ≤ 10^6。

### 关键知识
- **计数数组 / 桶 counting array**：值域只有 10^6，可以直接开数组标记
- **"固定一个，查找另一个"**的枚举技巧

### 核心洞察
枚举右边的楼 j。与它相距够远的左边的楼恰好是 1..j−K，这是一个**随 j 增大只增不减的前缀**。
所以每当 j 前进一步，就把楼 j−K 的高度加入"已见集合 seen"，然后查询 seen 里是否有 $H_j$ − X 或 $H_j$ + X。

### 分步讲解
1. **暴力 O(N²)**（Subtask 1）：双重循环，j ≥ i + K。
2. **K = 1, X = 0**（Subtask 2）：就是问"有没有两个相同高度" → 计数数组。
3. **X = 0**（Subtask 3）：记录每个高度最后出现的位置，看是否 ≥ K 远……也可以直接用满分方法。
4. **满分**：扫描 j，加入 H[j−K]，查 seen[$H_j$ − X]、seen[$H_j$ + X]。注意 $H_j$ − X 可能 < 1，$H_j$ + X 可能到 2×10^6，数组开够。

### 复杂度
O(N + 值域)。

### C++ 代码
```cpp
// AIIO 2025 P1 - Buildings
// 方法：枚举右边的楼 j + 计数数组 counting array（"已见集合"随 j 只增不减）
#include <bits/stdc++.h>
using namespace std;

int n, K, X;
int h[200010];
bool seen[2000010];                 // seen[v]：某栋"足够远"的楼高度为 v

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> K >> X;
    for (int i = 1; i <= n; i ++)
        cin >> h[i];

    // 考察 j 之前，把 i = j-K 放进已见集合；然后查 h[j]-X 和 h[j]+X
    for (int j = K + 1; j <= n; j ++){
        seen[h[j - K]] = true;
        int lo = h[j] - X, hi = h[j] + X;
        if ((lo >= 1 && seen[lo]) || seen[hi]){
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}
```

---

## Problem 2：Retail Empire

### 题意
初始每天利润 A。每天结束时可以用**当天的利润**开新店：N 种店，第 i 种花费 $C_i$，之后每天多赚 $P_i$；**每种店每天最多开一家**（不同天可以重复开）。没花完的钱存起来、不能再用于开店。问最早第几天日利润 ≥ K。N ≤ 50，K ≤ 150 000。

### 关键知识
- **贪心 greedy** 及其正确性证明（支配 dominance / 单调性 monotonicity）
- **0/1 背包 0/1 knapsack**：这是向学生正式介绍 DP 的经典模型

### 核心洞察
1. **每天的决策是一个 0/1 背包**：预算 = 当天利润 p，物品 = N 种店（每种最多选一次），重量 $C_i$，价值 $P_i$。设 best[b] = 预算 b 时能增加的最大日利润。
2. **每天都取最大增量就是最优的**：设我们的策略每天利润为 $p_t$，任何其他策略为 $p'_t$。
   - best[b] 关于 b 单调不减（预算多不会更差）
   - 若 $p'_t \le p_t$，则 $p'_{t+1} = p'_t + (\text{某个可行增量}) \le p'_t + \mathrm{best}[p'_t] \le p_t + \mathrm{best}[p_t] = p_{t+1}$
   - 归纳 induction：贪心每天的利润都不低于任何策略 → 最早达到 K。
3. 背包只需要算一次（best[0..K]），之后每天 O(1) 模拟。

### 分步讲解

**第 1 步：Subtask 1（所有 $C_i$ = 1）**
- 预算 p 就是"最多开 p 家店"，当然选 P 最大的 p 种。排序后贪心，模拟每天。
- 在这里先让学生接受"每天都尽量多赚"的想法。

**第 2 步：$C_i$ 不同时，一天之内怎么选？**
- 举反例说明"按性价比 P/C 贪心"不对：预算 10，店 (6, 6)、(5, 5)、(5, 5)。性价比全是 1，但选 (6,6) 后剩 4 买不了任何东西，只得 6；选两个 (5,5) 得 10。
- 引出 **0/1 背包**。

**第 3 步：0/1 背包 DP（新知识，详细讲）**
- 状态：`best[b]` = 预算为 b 时的最大价值。
- 逐个考虑物品 i，对每个 b：$\mathrm{best}[b] = \max(\mathrm{best}[b], \mathrm{best}[b - C_i] + P_i)$。
- **为什么 b 要从大到小循环？** 从大到小时，$\mathrm{best}[b - C_i]$ 还是"没用过物品 i"的旧值，保证每个物品只用一次。若从小到大，同一物品会被重复使用（那是"完全背包 unbounded knapsack"）。建议让学生两种都写，用样例对比。

**第 4 步：证明贪心（洞察 2）**，然后组装：`while (p < K) { p += best[p]; day++; }`

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（$C_i$ = 1） | 排序 + 贪心 |
| 2（K ≤ 400） | 每天现做一次背包也够快 |
| 3 | 预处理一次背包 O(N·K)，再 O(天数) 模拟 |

### 常见错误
- 背包内层循环从小到大 → 物品被重复使用。
- 以为花不完的钱可以留到第二天 → 题目说不行，所以每天的预算只是当天利润。

### C++ 代码
```cpp
// AIIO 2025 P2 - Retail Empire
// 方法：Greedy（每天都取最大增量，靠单调性证明）+ 0/1 背包 0/1 knapsack（DP）
#include <bits/stdc++.h>
using namespace std;

int n, A, K;
int c[60], p[60];
long long best[150010];             // best[b]：预算 b 时，每种店最多开一家，能增加的最大日利润

int main(){
    cin >> n >> A >> K;
    for (int i = 1; i <= n; i ++)
        cin >> c[i] >> p[i];

    // 1) 0/1 背包：b 从大到小，保证每种店只用一次
    for (int i = 1; i <= n; i ++)
        for (int b = K; b >= c[i]; b --)
            best[b] = max(best[b], best[b - c[i]] + p[i]);

    // 2) 模拟：每天把当天利润全部用在"最赚的组合"上
    long long profit = A;
    int day = 1;
    while (profit < K){
        profit += best[profit];     // profit < K，下标不会越界
        day ++;
    }

    cout << day << endl;
    return 0;
}
```

---

## Problem 3：Amazing Game II

### 题意
迷宫是一个连通无向图（N ≤ 1000 个房间，M ≤ 2000 条通道）。Amy 沿给定路径 $A_1$, …, $A_K$ 走（K ≤ 200 000）。Q 局游戏，第 i 局 Amy 从 $A_i$ 出发，Bruno 从 $B_i$ 出发。每一轮 Amy 走到路径下一个房间，Bruno 可以原地不动或走到相邻房间。若 Bruno **原地不动**且 Amy **走进了他所在的房间**，Bruno 得 1 分。求每局 Bruno 最多得几分。

### 关键知识
- **BFS**，以及对每个点都做一次 BFS 得到全源最短路 all-pairs shortest path（N 只有 1000）
- **把游戏建模为"得分时刻序列"**
- **贪心 + 交换论证 exchange argument**
- **双指针 two pointers**
- **倒推计数**（类似 DP 的"从后往前"）

### 核心洞察
1. **重新表述得分条件**：把时刻记为 Amy 所在的下标 t（第 i 局开始时是 t = i）。Bruno 在时刻 t 得分 ⇔ 他在时刻 t−1 和时刻 t 都在房间 $A_t$。
2. **两次得分之间的条件**：
   - 第一次得分在时刻 t：需要 $\mathrm{dist}(B, A_t) \le  t - 1 - i$（在时刻 t−1 前赶到）。
   - 在时刻 t 得分后，下一次在 t2 得分：需要 $\mathrm{dist}(A_t, A_{t2}) \le  t2 - 1 - t$。
3. **贪心：每次都选最早能得分的时刻**。交换论证：若最优解第一次得分在 t' 而贪心在更早的 t，那么从 $A_t$ 赶到最优解的下一个得分点 $A_{t2}$ 也来得及，因为
   $\mathrm{dist}(A_t, A_{t2}) \le  \mathrm{dist}(A_t, A_{t'}) + \mathrm{dist}(A_{t'}, A_{t2}) \le  (t' - t) + (t2 - 1 - t') = t2 - 1 - t$
   （Amy 从 t 走到 t' 用了 t' − t 步，所以 dist($A_t$, $A_{t'}$) ≤ t' − t）。
4. **"下一次最早得分"的几何意义**：dist($A_t$, $A_{t2}$) ≤ t2 − t − 1 ⇔ Amy 从 $A_t$ 走到 $A_{t2}$ 的这段路**不是最短路 not a geodesic**。所以 nextT[t] = Amy 从 t 开始的路第一次"绕路"的时刻。
   - 最短路的子路径仍是最短路 → 这个"第一次绕路"的位置随 t 单调不减 → **双指针** O(K)。
5. **nextT 构成一条链**：score[t] = 1 + score[nextT[t]]，从后往前算。每局答案 = score[第一次能得分的时刻]。
6. 第一次得分的时刻最多在 i + (图的直径 + 1) 之内（Bruno 总能在直径步内到达任何地方），所以直接往后扫即可。

### 分步讲解

**第 1 步：Subtask 1（K = 3, $A_1$ = $B_1$）**：只有 2 轮，手动分析：Bruno 能得分 ⇔ $A_3$ 等于 $A_1$ 或与 $A_1$ 相邻（他在第 1 轮走到 $A_3$，第 2 轮等 Amy）。让学生自己推出来。

**第 2 步：暴力 DP（Subtask 2，K ≤ 1000）**
- `V[j][v]` = 第 j 轮开始前 Bruno 在 v 时，之后最多得分。
- $V[j][v] = \max( [v == A_{j+1}] + V[j+1][v],  \max_{u \text{ 相邻}} V[j+1][u] )$
- 这是很好的 DP 练习，也是之后对拍用的标准答案。复杂度 O(K·(N+M))，K 大时太慢。

**第 3 步：换个角度——只关心"在哪些时刻得分"**（洞察 1, 2）。画时间轴，标出得分时刻。

**第 4 步：贪心 + 交换论证**（洞察 3）。建议板书三角不等式那一行。

**第 5 步：用"是否最短路"求 nxt**（洞察 4）
- 先对每个房间 BFS，得到 dist 表（1000 × 1000，用 short 存只需 2MB）。
- 双指针：g 表示"$A_t$..$A_g$ 仍是最短路"的最大 g；对下一个 t，g 不会变小。

**第 6 步：链上计数 + 回答询问**（洞察 5, 6）。

**部分分提示**：题目给 30% 分数只需判断答案是否为 0 —— 即判断是否存在第一次得分的时刻。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1 | 手动分析 2 轮 |
| 2（K ≤ 1000） | 时间 × 房间的 DP |
| 3（一局，$A_1$ = $B_1$） | 贪心 + nxt 链 |
| 4（$A_i$ = $B_i$） | 答案就是 score[nextT[i]] 链 |
| 5 | 完整做法：O(N(N+M) + K + Q·直径) |

### 常见错误
- 把"得分"理解成 Bruno 走进 Amy 的房间 → 必须是 Bruno 不动、Amy 走进来。
- 第一次得分的条件是 `≤ t − 1 − i`，差一错误 off-by-one 很常见。
- dist 表用 `int dist[1010][1010]` 也可以（4MB），但 `short` 更省。

### C++ 代码
```cpp
// AIIO 2025 P3 - Amazing Game II
// 方法：全源 BFS（N <= 1000）+ Greedy（每次选最早能得分的时刻，交换论证）
//       + Two Pointers（Amy 的路"第一次不是最短路"的位置单调）+ 从后往前计数
#include <bits/stdc++.h>
using namespace std;

int n, m, K, Q;
int head[1010], nxt[4010], to[4010], cnt;   // 邻接表（链式前向星）
short dist[1010][1010];                     // dist[u][v]：u 到 v 的最短距离
int A[200010];
int nextT[200010];      // nextT[t]：在时刻 t 于 A[t] 得分后，下一次最早得分的时刻（K+1 表示没有）
int score[200010];      // score[t]：在时刻 t 得分之后（含这一分），最多还能得几分
int que[1010];

void addEdge(int u, int v){
    cnt ++;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void bfs(int s){
    for (int i = 1; i <= n; i ++)
        dist[s][i] = -1;
    int qh = 1, qt = 0;
    dist[s][s] = 0;
    que[++ qt] = s;
    while (qh <= qt){
        int u = que[qh ++];
        for (int e = head[u]; e; e = nxt[e])
            if (dist[s][to[e]] < 0){
                dist[s][to[e]] = dist[s][u] + 1;
                que[++ qt] = to[e];
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i ++){
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    cin >> K;
    for (int i = 1; i <= K; i ++)
        cin >> A[i];

    // 1) 从每个房间做一次 BFS
    for (int s = 1; s <= n; s ++)
        bfs(s);

    // 2) 双指针：g = 使 A[t..g] 仍是最短路的最大下标，随 t 单调不减
    int g = 1;
    for (int t = 1; t <= K; t ++){
        if (g < t)
            g = t;
        while (g + 1 <= K && dist[A[t]][A[g + 1]] == g + 1 - t)
            g ++;
        nextT[t] = g + 1;
    }

    // 3) 沿 nextT 链从后往前计数
    for (int t = K; t >= 1; t --){
        score[t] = 1;
        if (nextT[t] <= K)
            score[t] += score[nextT[t]];
    }

    // 4) 每一局：找第一个能得分的时刻 t（dist(B, A[t]) <= t - 1 - i）
    cin >> Q;
    for (int i = 1; i <= Q; i ++){
        int b;
        cin >> b;
        int ans = 0;
        for (int t = i + 1; t <= K; t ++)
            if (dist[b][A[t]] <= t - 1 - i){
                ans = score[t];
                break;
            }
        cout << ans << "\n";
    }
    return 0;
}
```

---

## Problem 4：Kth Number（交互题 interactive problem）

### 题意
主持人有排列 P（长度 N）和秘密的 K（1 ≤ K ≤ M）。每次询问选 M 个不同下标，主持人返回这些位置的值中**第 K 小**的那个。已知 N、M，求 K。满分要求询问次数 Q ≤ ⌈N/2⌉ + 1。评测器可能是**自适应的 adaptive**（根据你的询问改变 P）。N ≤ 200。

### 关键知识
- **交互题格式**：实现函数 `findK`，调用 `ask_host`，不写 main、不读写标准输入输出
- **排名 rank 推理**：删掉/替换一个元素后，第 K 小会怎样变化
- **分类讨论 case analysis**：M 小和 M 大用不同策略
- **对手论证 adversary argument**：自适应评测 → 程序必须对所有"与已知回答一致"的情况都正确

### 核心洞察

**情况 A：M ≤ ⌈N/2⌉ —— 用 M+1 次询问**
- 取集合 S = {0, 1, …, M}（M+1 个）。依次询问 S \ {j}。
- 设 S 中的值从小到大为 $v_1$ < $v_2$ < … < $v_{M+1}$。
  - 去掉的元素排名 ≤ K → 第 K 小变成 $v_{K+1}$（较大的答案）
  - 去掉的元素排名 > K → 第 K 小仍是 $v_K$（较小的答案）
- 恰好有 K 个元素排名 ≤ K，所以 **K = 得到较大答案的次数**。
- M+1 ≤ ⌈N/2⌉ + 1 ✓。（Subtask 1 的 M = 2 恰好用 3 次。）

**情况 B：M > ⌈N/2⌉ —— 用"固定底座 T + 探针 z"**
- 取 T = 前 M−1 个下标，U = 剩下的 u = N−M+1 个下标。对每个 z ∈ U 询问 T ∪ {z}。
- 设 T 排序后为 $t_1$ < … < $t_{M-1}$，令 α = $t_{K-1}$，β = $t_K$。则
  **答案 = clamp($P_z$, α, β)**（$P_z$ 比 α 小就返回 α，比 β 大就返回 β，否则返回 $P_z$ 本身）。
- 利用"P 是 1..N 的排列"，值本身就是它在全体中的排名：若 mx 是所有答案的最大值且它是 β 或某个中间的 $P_z$，则
  **K = mx − (答案中 < mx 的个数)**。
- 唯一的例外：**所有答案都相同（记为 x）**。这时要么 U 全在 β 上方（假设 H：K = x），要么全在 α 下方（假设 L：K = x + 1 − u）。
- **分辨 H 和 L**：询问 T \ {t} ∪ {z1, z2}（z1, z2 ∈ U）：
  - 答案 > x ⇒ H；答案 < x ⇒ L；
  - 答案 = x：在 H 下说明 t 的排名 > K（这样的 t 至多 M−1−$K_H$ 个），在 L 下说明 t 的排名 ≤ K−2（至多 $K_L$−2 个）。
  - 换不同的 t 重复；某个假设"容量用完"就被排除。可以证明总次数仍 ≤ ⌈N/2⌉ + 1。

### 分步讲解

**第 1 步：先玩样例**：N = 5, M = 3, K = 2, P = [3, 1, 5, 4, 2]。
- 情况 A：S = {0,1,2,3}，值 {3,1,5,4}，排好序 1,3,4,5。
- 去掉 0（值 3，排名 2 ≤ K）→ 答案 4；去掉 1（值 1）→ 4；去掉 2（值 5）→ 3；去掉 3（值 4）→ 3。
- 较大答案 4 出现 2 次 → K = 2 ✓，用了 4 次 = ⌈5/2⌉ + 1。

**第 2 步：Subtask 2（M = N−1）特别好讲**：询问"全部去掉一个"，答案只可能是 K 或 K+1（因为值就是 1..N）。这里能引导学生意识到"值 = 全局排名"这个关键性质。

**第 3 步：情况 B 的 clamp 公式**。画一条数轴，标出 T 的值，α、β 是"第 K−1 小"和"第 K 小"，z 插进来时第 K 小落在哪里。

**第 4 步：为什么 K = mx − (#答案 < mx)？**
- 若 mx = β = $t_K$：≤ β 的值有 β 个 = T 中 K 个 + U 中 $P_z$ < β 的个数，而 $P_z$ < β ⇔ 答案 < β。
- 若 mx 是中间值 $P_z$：同理推导，结果一致。

**第 5 步：全部相同的情况**（本题最难的部分）。样例 3 的一个场景可作演示：N = 6, M = 5, K = 3, P = [4,5,6,1,2,3]。
- T = {0,1,2,3}（值 4,5,6,1 → 排序 1,4,5,6），α = 4, β = 5；U = {4,5}（值 2,3）。
- 两次探针答案都是 clamp → 4，全部相同 x = 4。假设 H：K = 4；假设 L：K = 4 + 1 − 2 = 3。
- 询问 T \ {0} ∪ {4, 5}：值 {5,6,1,2,3}，第 3 小 = 3 < 4 ⇒ L ⇒ K = 3 ✓。

**第 6 步：讨论"自适应评测"**：程序的每一步推理都只依赖"已得到的回答"，而不是猜测 P，所以对自适应评测同样正确。

### 子任务阶梯
| 子任务 | 思路 |
|---|---|
| 1（M = 2） | 情况 A，3 次 |
| 2（M = N−1） | 情况 B（或"全部去掉一个"+ 淘汰法） |
| 3 | 情况 A / B 分类，≤ ⌈N/2⌉ + 1 次 |

### 常见错误
- 询问的下标重复或个数不是 M → 直接 0 分。
- 多组场景之间忘记清空全局变量（本代码不使用全局状态）。
- 在"全部相同"时直接猜一个 → 自适应评测会让你错。

### C++ 代码（不含 main，需与官方 kthnumber.h、grader.cpp 一起编译）
```cpp
// AIIO 2025 P4 - Kth Number（交互题 interactive）
// 方法：分类讨论 case analysis
//   情况 A（M 较小）：S = {0..M}，依次去掉一个元素询问，K = 较大答案出现的次数
//   情况 B（M 较大）：固定底座 T + 探针 z，答案 = clamp(P_z, alpha, beta)，利用"值 = 全局排名"
// 注意：官方接口 ask_host 的参数是 std::vector<int>，这是本题唯一用到 vector 的地方
#include "kthnumber.h"
#include <bits/stdc++.h>
using namespace std;

int idx[210], res[210];

// 把数组 idx[1..cnt] 交给主持人（官方接口需要 vector）
int ask(int cnt){
    std::vector<int> I;
    for (int i = 1; i <= cnt; i ++)
        I.push_back(idx[i]);
    return ask_host(I);
}

int findK(int N, int M, int subtask){
    // ---------- 情况 A：M+1 次询问 ----------
    if (M <= (N + 1) / 2){
        int big = 0;
        for (int j = 0; j <= M; j ++){
            int c = 0;
            for (int i = 0; i <= M; i ++)
                if (i != j)
                    idx[++ c] = i;
            res[j] = ask(c);
            big = max(big, res[j]);
        }
        int K = 0;                          // 去掉"排名 <= K"的元素，得到较大的答案
        for (int j = 0; j <= M; j ++)
            if (res[j] == big)
                K ++;
        return K;
    }

    // ---------- 情况 B：T = {0..M-2}，U = {M-1..N-1} ----------
    int u = N - M + 1;
    int mx = 0, mn = N + 1;
    for (int k = 1; k <= u; k ++){
        int z = M - 2 + k;                  // 第 k 个探针
        int c = 0;
        for (int i = 0; i <= M - 2; i ++)
            idx[++ c] = i;
        idx[++ c] = z;
        res[k] = ask(c);
        mx = max(mx, res[k]);
        mn = min(mn, res[k]);
    }
    if (mx != mn){
        // 最大答案是 beta 或某个夹在中间的 P_z：K = mx - (答案 < mx 的个数)
        int less = 0;
        for (int k = 1; k <= u; k ++)
            if (res[k] < mx)
                less ++;
        return mx - less;
    }

    // 所有答案都等于 x：假设 H（U 全在上方，K = x）或假设 L（U 全在下方，K = x+1-u）
    int x = mx;
    int KH = x, KL = x + 1 - u;
    int capH = M - 1 - KH;                  // H 成立时，T 中排名 > K 的个数
    int capL = KL - 2;                      // L 成立时，T 中排名 <= K-2 的个数
    int eq = 0;
    for (int t = 0; t <= M - 2; t ++){
        if (capH < 0 || eq > capH)          // H 已不可能
            return KL;
        if (capL < 0 || eq > capL)          // L 已不可能
            return KH;
        int c = 0;                          // 询问 T \ {t} ∪ {两个探针}
        for (int i = 0; i <= M - 2; i ++)
            if (i != t)
                idx[++ c] = i;
        idx[++ c] = M - 1;
        idx[++ c] = M;
        int r = ask(c);
        if (r > x)
            return KH;
        if (r < x)
            return KL;
        eq ++;
    }
    if (eq > capH)
        return KL;
    return KH;
}
```
