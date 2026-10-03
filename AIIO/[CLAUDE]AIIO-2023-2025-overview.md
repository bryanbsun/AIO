# AIIO 2023–2025 总览（Overview）

> AIIO = Australian Invitational Informatics Olympiad。题目来源：https://orac.amt.edu.au/hub/aiio/
> 时间有限的学生请直接看最后一节「时间有限怎么办：主攻每年前两题」。
> 详细讲解见同目录下三个文件：`[CLAUDE]AIIO-2023-analysis.md`、`[CLAUDE]AIIO-2024-analysis.md`、`[CLAUDE]AIIO-2025-analysis.md`。

## 题目与知识点速查

| 年份 | 题目 | 核心技巧 | 学生的新知识 |
|---|---|---|---|
| 2023 | Sculpture III | DP + 前缀最大值 prefix max + 后缀最小值 suffix min | DP 入门 |
| 2023 | Pinnacle | 单调栈 monotonic stack + 稀疏表 sparse table + 链上求和 | 单调栈、稀疏表 |
| 2023 | Electrical Fault | 多源 Dijkstra multi-source + 来源标签 owner + 枚举边 | 堆 heap、Dijkstra |
| 2024 | Speed Friending | 归并模型 merge → 比较左右最大距离；线段树 segment tree | 线段树 |
| 2024 | Overcycle | 所有捷径经过 1 或 N → 两次 Dijkstra | Dijkstra |
| 2024 | Curator Catastrophe | 置换环 cycles + 下界 lower bound + 构造 construction | 置换环 |
| 2025 | Buildings | 计数数组 counting array + 滑动已见集合 | — |
| 2025 | Retail Empire | 贪心 greedy（支配性证明）+ 0/1 背包 knapsack | 0/1 背包 |
| 2025 | Amazing Game II | 全源 BFS + 交换论证 exchange argument + 双指针 two pointers | 建模能力 |
| 2025 | Kth Number | 交互题 interactive + 排名推理 rank reasoning + 分类讨论 | 交互题、对手论证 |

## 建议的教学顺序（按学生目前基础：会枚举、模拟、贪心、二分，未学 DP 和堆）

1. **Buildings (2025)** —— 热身，复习计数数组与"固定一个找另一个"。
2. **Speed Friending (2024)** —— 先只做无修改版本（前缀/后缀数组），重点训练"观察 + 证明"。之后再引入线段树。
3. **Sculpture III (2023)** —— DP 第一课：House Robber → 一般区间限制。
4. **Retail Empire (2025)** —— DP 第二课：0/1 背包；同时练习贪心正确性证明。
5. **Electrical Fault (2023)** —— 引入堆 heap（数组手写小根堆）与 Dijkstra。
6. **Overcycle (2024)** —— Dijkstra 的直接应用 + 图结构观察。
7. **Pinnacle (2023)** —— 单调栈、稀疏表。
8. **Curator Catastrophe (2024)** —— 置换环，"下界 + 构造"的完整论证。
9. **Amazing Game II (2025)** —— 综合建模 + 交换论证。
10. **Kth Number (2025)** —— 交互题，最后作为挑战。

## 反复出现的思想（Recurring ideas）

- **先证下界，再构造达到下界**（Curator、Pinnacle、Electrical Fault 的边界边论证）。
- **贪心的正确性靠"交换论证 exchange argument"或"支配 dominance"**（Retail Empire、Amazing Game II、Speed Friending）。
- **把复杂过程化简为一个量的比较**（Speed Friending：只看左右最大距离；Overcycle：只看经过 1 或 N）。
- **预处理 + O(1) 查询**（前缀和、后缀最值、稀疏表、链上后缀和）。

---

## 时间有限怎么办：主攻每年前两题（Focus on Problems 1 & 2）

> 适用对象：准备时间不多、目标是"稳拿分"而不是冲高分的学生。
> 原则：**AIIO 的分数来自子任务 subtask，而不是整题**。每年前两题的大部分子任务只需要基础工具；后两题也各有几档"白送分"。先把能拿的分全拿到，再考虑进阶。

### 1. 最小工具箱（按"性价比"排序）

| 优先级 | 工具 | 学习成本 | 能解锁的分数（2023–2025 前两题 + 后两题低档） |
|---|---|---|---|
| ① | 前缀和 prefix sum、计数数组 counting array、前缀/后缀最值 prefix/suffix max/min | 低（已会） | Buildings 100、Speed Friending 70、Overcycle 子任务 1 |
| ② | BFS + 队列 queue | 低 | Electrical Fault 55、Overcycle 子任务 5（30 分） |
| ③ | 入门 DP：House Robber、0/1 背包 0/1 knapsack | 中 | Sculpture III 100、Retail Empire 100、Amazing Game II 40 |
| ④ | 交互题格式 interactive format（只写函数、调用 `ask_host`） | 低 | Kth Number 70（见第 3 节） |
| ⑤ | 堆 heap（手写）+ Dijkstra | 中 | Electrical Fault 再 +45、Overcycle 再 +35 |
| ⑥ | 线段树 segment tree | 高 | Speed Friending 再 +30（时间紧可以放弃） |

**结论**：只要掌握 ①–④，三年里每年都能拿到可观的分数；⑤ 是下一步最值得投入的；⑥ 可以先不学。

### 2. 逐题得分地图（Score map）

图例：✅ 必拿 must-get　🟡 值得争取 worth trying　⛔ 时间紧可以放弃 skip

#### 2023 Problem 1：Sculpture III

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 15 | $a_i$ = 1：从左到右能选就选（贪心 greedy） | 枚举 | ✅ |
| 2 | 15 | 同上，加后缀最小值检查冲突 | ① | ✅ |
| 3 | 30 | 相邻限制 = House Robber DP | ③ | ✅ |
| 4 | 20 | 一般 DP，O(N²) 找合法的上一个 | ③ | ✅ |
| 5 | 20 | 后缀最小值 + 前缀最大值，O(N + M) | ①③ | ✅（离满分只差一步） |

**可拿：100 分。** 这是全三年最适合"时间有限的学生"拿满分的题。

#### 2023 Problem 2：Electrical Fault

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 15 | K = 2、边权 1：从 $x_1$ 做 BFS | ② | ✅ |
| 3 | 40 | 边权 1：**多源 BFS** + owner 标签 + 枚举边 | ② | ✅（本题最大的一块分） |
| 2 | 15 | K = 2、边权任意：Dijkstra | ⑤ | 🟡 |
| 4 | 30 | 多源 Dijkstra + owner + 枚举边 | ⑤ | 🟡 |

**不学堆：55 分；学了 Dijkstra：100 分。** 子任务 3 的"owner 标签 + 边界边"是核心思想，用 BFS 就能讲清楚，学了 Dijkstra 以后几乎一行不改就能拿满分。

#### 2024 Problem 1：Speed Friending

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 20 | $p_s$ = 0：比较左右两边的最大值 | ① | ✅ |
| 2 | 15 | 一次询问：O(N) 求左右最大距离 | ① | ✅ |
| 3 | 35 | 无修改：前缀/后缀 max、min 数组，每次 O(1) | ① | ✅ |
| 4 | 30 | 有修改：线段树 | ⑥ | ⛔ |

**不学线段树：70 分。** 关键是"最后一个朋友只能是 1 或 N、只看左右最大距离"这个观察（见 2024 讲义）。

#### 2024 Problem 2：Overcycle

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 10 | 无捷径：pre[t] − pre[s] | ① | ✅ |
| 3 + 4 | 25 | B = 0：**两次扫描求 d1**（不需要堆，代码见下） | ① | ✅ |
| 5 | 30 | 边权 1：从 1 和 N 各做一次 BFS，套公式 | ② | ✅ |
| 2 | 20 | N ≤ 1000：数组版 Dijkstra（O(N²)，不用堆）求 d1、dN，套公式 | 简化版 ⑤ | 🟡 |
| 6 | 15 | 两次堆优化 Dijkstra | ⑤ | 🟡 |

**不学堆：65 分（会写数组版 Dijkstra：85 分）；学了堆：100 分。**
所有子任务共用同一个核心观察：`答案 = min(只走路, d1[s] + d1[t], dN[s] + dN[t])`，区别只在于 d1、dN 怎么算。

B = 0 时，d1[v] = 从 1 坐一次捷径到某个 x、再沿路走到 v 的最小值（坐多次捷径必然要回到 1，没有意义）。把"捷径直达 x 的代价" c[x] 记下来（c[1] = 0），就是 `d1[v] = min over x ( c[x] + |pre[v] − pre[x]| )`，拆成"x 在左边"和"x 在右边"各扫一遍：

```cpp
// Overcycle 子任务 3、4（B = 0），不需要堆。已与暴力对拍 1500 组。
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 200005;
const ll INF = 4000000000000000000LL;
ll pre[MAXN], c[MAXN], d1[MAXN];

int main() {
    int n, A, B, q;
    scanf("%d", &n);
    pre[1] = 0;
    for (int i = 1; i < n; i++) {
        ll d;
        scanf("%lld", &d);
        pre[i + 1] = pre[i] + d;
    }
    for (int i = 1; i <= n; i++) c[i] = INF;
    c[1] = 0;                                   // 站在 1 本身, 代价 0
    scanf("%d", &A);
    for (int i = 0; i < A; i++) {
        int x; ll k;
        scanf("%d %lld", &x, &k);
        c[x] = min(c[x], k);                    // 1 -> x 的捷径, 取最便宜的
    }
    scanf("%d", &B);                            // 本子任务 B = 0
    ll best = INF;                              // x 在 v 左边: c[x] - pre[x] + pre[v]
    for (int v = 1; v <= n; v++) {
        if (c[v] < INF) best = min(best, c[v] - pre[v]);
        d1[v] = best + pre[v];
    }
    best = INF;                                 // x 在 v 右边: c[x] + pre[x] - pre[v]
    for (int v = n; v >= 1; v--) {
        if (c[v] < INF) best = min(best, c[v] + pre[v]);
        d1[v] = min(d1[v], best - pre[v]);
    }
    scanf("%d", &q);
    while (q--) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld\n", min(pre[t] - pre[s], d1[s] + d1[t]));
    }
    return 0;
}
```

#### 2025 Problem 1：Buildings

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 25 | 双重循环 O(N²) | 枚举 | ✅ |
| 2 | 30 | K = 1、X = 0：有没有重复高度 → 计数数组 | ① | ✅ |
| 3 + 4 | 45 | 扫描 j，把 H[j−K] 放入 seen 数组，查 $H_j$ ± X | ① | ✅ |

**可拿：100 分。** 满分做法只比子任务 2 多几行。

#### 2025 Problem 2：Retail Empire

| 子任务 | 分值 | 做法 | 工具 | 建议 |
|---|---|---|---|---|
| 1 | 35 | $C_i$ = 1：每天选 P 最大的若干种店（排序 + 贪心） | 排序 | ✅ |
| 2 | 35 | K ≤ 400：每天做一次 0/1 背包 | ③ | ✅ |
| 3 | 30 | 背包只预处理一次，每天 O(1) 模拟 | ③ | ✅ |

**可拿：100 分。** 子任务 1 → 2 正好用来引出"为什么按性价比贪心不对、需要背包"。

### 3. 后两题里的"白送分"（Cheap points in Problems 3 & 4）

做完前两题还有时间时，按下表顺序去拿后两题的低档分：

| 题目 | 子任务 | 分值 | 做法 | 难度 |
|---|---|---|---|---|
| **2025 P4 Kth Number** | 1, 2, 3 | **最多 70** | 只写"情况 A"：询问 S = {0..M} 去掉每个 j，K = 较大答案出现的次数。M = 2 时 3 次（25 分）；一般 M+1 ≤ N 次（子任务 2 得 15、子任务 3 得 30） | ★（约 10 行，但要先熟悉交互题格式） |
| 2025 P3 Amazing Game II | 1, 2 | 40 | 子任务 1 手推（$A_3$ 等于或相邻于 $A_1$ 就得 1 分）；子任务 2 用"时间 × 房间"的 DP | ★★（需要 ③） |
| 2024 P3 Curator Catastrophe | 1, 2 | 20 | 高度互不相同 → 所有交换都合法，答案 N − C（置换环），逐个把画送到位 | ★★ |
| 2023 P3 Pinnacle | 1 | 10 | 单次询问：找最大值，两边各扫一遍补成前缀/后缀最大值 | ★ |

特别提醒：**Kth Number 的 70 分性价比极高**，但交互题格式（不写 main、不读输入、调用 `ask_host`）必须提前练过，否则考场上容易因为格式错误拿 0 分。

### 4. 预估得分（Estimated scores）

| 年份 | 只用 ①–④（不学堆） | 再学 ⑤ Dijkstra | 说明 |
|---|---|---|---|
| 2023 | 100 + 55 + 10 = **165** | **210** | Sculpture 满分 + Electrical 多源 BFS + Pinnacle 子任务 1 |
| 2024 | 70 + 65 + 20 = **155** | **190** | Speed 无修改部分 + Overcycle 多数子任务 + Curator $h_i$ = i |
| 2025 | 100 + 100 + 40 + 70 = **310** | 310 | 2025 前两题都不需要堆，后两题低档分也多 |

### 5. 建议的短期训练计划（6 次课）

| 课次 | 内容 | 练习题 |
|---|---|---|
| 1 | 计数数组、前缀和、前缀/后缀最值；"读子任务 → 定目标"的习惯 | Buildings（满分）、Speed Friending 子任务 1–3 |
| 2 | DP 入门：状态、转移、答案；House Robber | Sculpture III（全部子任务，逐档推进） |
| 3 | 0/1 背包；贪心为什么需要证明 | Retail Empire（满分） |
| 4 | BFS、多源 BFS、owner 标签 | Electrical Fault 子任务 1、3；Overcycle 子任务 5 |
| 5 | 图结构观察 + 两次扫描；交互题格式 | Overcycle 子任务 1、3、4；Kth Number 情况 A |
| 6 | 模拟考试：限时做一整套（建议 2025），练习考场策略 | 2025 全套，目标 ≥ 250 |

时间再多一些时，第 7 课学堆 heap（手写）+ Dijkstra，把 Electrical Fault 和 Overcycle 补满。

### 6. 考场策略（Exam tactics）

1. **先读完所有题的子任务表**，用 5 分钟标出每档"能不能做、要多久"，按性价比排序，不要按题号死磕。
2. **先交最简单的子任务**，确保有分；再在同一份代码里加更快的做法（用 if 按数据范围分情况）。
3. **暴力程序别删**：它是后面对拍 stress test 的标准答案。
4. **long long**：Pinnacle、Overcycle、Electrical Fault 的答案都可能超过 int。
5. **交互题**：先交一个"保底"版本（例如 Kth Number 的情况 A），确认格式正确再优化。
6. 一道题卡住超过 30 分钟没有进展，就去拿别的题的低档分。
