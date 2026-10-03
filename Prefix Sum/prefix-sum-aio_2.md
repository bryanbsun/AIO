# 前缀和（Prefix Sum）完全教程 —— 面向澳洲 AIO

> **本材料对照 ORAC 官方训练页 [Prefix Sums](https://orac.amt.edu.au/hub/train/aio-prefixsum) 编写。**
> 核心概念、引例（Mansion）与练习（Alien）与 ORAC 保持一致；在此基础上，**额外补充**了
> ORAC 该页没有涉及、但你需要的相关形式：差分数组、二维前缀和、后缀和、前缀/后缀极值。
> 重要术语均**附英文**，方便对照 AIO 的英文题面。
>
> 适用对象：已掌握基本数据结构与算法，但**尚未学动态规划和高级数据结构**（线段树、树状数组、稀疏表）的同学。
> 语言：C++（只用 `<iostream>`，不使用模板容器与 C++11 之后的新特性）。

---

## 术语中英对照表 (Glossary)

| 中文 | English | 说明 |
|------|---------|------|
| 前缀和 | **Prefix Sum** | 从数组开头累加到当前位置的和 |
| 预计算 / 预处理 | **Precomputation** | 提前把结果算好，之后重复使用 |
| 区间 / 连续段 | **Interval / Contiguous section** | 数组中一段连续的元素 |
| 子数组 | **Subarray** | 区间的另一种叫法 |
| 子矩形 | **Subrectangle** | 二维网格里的一块矩形区域 |
| 时间复杂度 | **Time Complexity** | 用大 O 记号衡量算法快慢 |
| 前缀和表 | **Prefix sum table** | 又称累积和 (cumulative sums) / 部分和 (partial sums) |
| 差一错误 | **Off-by-one error** | 下标边界算错一位的常见 bug |
| 哨兵 | **Sentinel** | 放在边界的辅助值（例如 `s[0]=0`） |
| 差分数组 | **Difference Array** | 前缀和的逆运算，用于区间整体更新 |
| 二维前缀和 | **2D Prefix Sum** | 前缀和在网格上的推广 |
| 容斥原理 | **Inclusion–Exclusion** | "加加减减、去掉重复"的计数思想 |
| 后缀和 | **Suffix Sum / Postfix Sum** | 从数组末尾累加到当前位置的和 |
| 前缀最大值 / 最小值 | **Prefix Maxima / Prefix Minima** | 从开头到当前位置的最大 / 最小值 |
| 后缀最大值 / 最小值 | **Suffix Maxima / Suffix Minima** | 从当前位置到末尾的最大 / 最小值 |
| 逆运算 | **Inverse operation** | 能"抵消"的运算（如减法之于加法） |
| 滑动窗口 | **Sliding Window** | 让一个固定/可变长的窗口逐步移动 |
| 双指针 | **Two Pointers** | 两个下标协同移动的技巧 |
| 溢出 | **Overflow** | 数值超出数据类型能表示的范围 |
| 下标 | **Index** | 1-indexed（从 1 开始）/ 0-indexed（从 0 开始） |

---

## 目录

1. [核心思想：预计算 (Precomputation)](#1-核心思想预计算-precomputation)
2. [引例：Mansion (AIO 2007)](#2-引例mansion-aio-2007)
3. [一维前缀和 (1D Prefix Sum)](#3-一维前缀和-1d-prefix-sum)
4. [差分数组 (Difference Array)：前缀和的逆运算](#4-差分数组-difference-array前缀和的逆运算)
5. [二维前缀和 (2D Prefix Sum)](#5-二维前缀和-2d-prefix-sum)
6. [家族成员：后缀和与前缀/后缀极值](#6-家族成员后缀和与前缀后缀极值)
7. [关键区别：可逆 vs 不可逆](#7-关键区别可逆-vs-不可逆)
8. [综合例题](#8-综合例题)
9. [常见坑与注意事项](#9-常见坑与注意事项)
10. [复杂度速查表](#10-复杂度速查表)
11. [AIO 练习题（ORAC 链接）](#11-aio-练习题orac-链接)

---

## 1. 核心思想：预计算 (Precomputation)

算法设计里一个非常常用的套路叫**预计算 (Precomputation)**：
把一段本来会很慢的计算，通过**提前做一些准备工作**，让后续变快。

具体到本教程：很多题目会反复问同一个数组"某一段区间 (interval) 的总和"。
如果每次都现场从头加一遍，会很慢；如果我们先花一次 `O(N)` 把"前缀和表"准备好，
之后每次询问都能 `O(1)` 回答。**这就是"用预计算换查询速度"的思想，是竞赛里最基础也最重要的优化之一。**

---

## 2. 引例：Mansion (AIO 2007)

这是 ORAC 前缀和教程选用的引例，我们沿用它来体会前缀和的威力。

**题意（概括）**：给一个长度为 `N` 的整数数组，要找出**恰好包含 `K` 个元素的连续段
（interval / subarray）**，使这段的和最大，输出这个最大和。
（原题：[Mansion, AIO 2007](https://orac.amt.edu.au/problem/aio07mansionsen/)）

### 2.1 朴素做法 (brute force)

一共只有 `N - K + 1` 个可能的窗口（**注意差一错误 / off-by-one error**）。
逐个把每个窗口里的 `K` 个数加起来、取最大：

```cpp
long long best = -1;
for (int start = 1; start + K - 1 <= N; start++) {
    long long cur = 0;
    for (int i = 0; i < K; i++) cur += a[start + i];   // 内层 O(K)
    if (cur > best) best = cur;
}
```

外层 `O(N)`、内层 `O(K)`，总时间复杂度 (time complexity) 是 **`O(N·K)`**。
在 Mansion 里这个做法**只能拿 50 / 100 分**——慢就慢在内层每次都把窗口的和从头重算一遍。有没有更快的办法？

### 2.2 用前缀和优化到满分

答案就是前缀和：先 `O(N)` 预计算前缀和表，之后**每个窗口的和用一次减法 `O(1)` 得到**，
总复杂度降到 **`O(N)`**，可拿满 **100 / 100**。具体公式和代码见第 3 节，我们会在 3.5 回到这道题。

> 补充：ORAC 还有一篇 [Two Pointers（双指针 / 滑动窗口）](https://orac.amt.edu.au/hub/train/aio-twopointers) 教程，
> 用**滑动窗口 (sliding window)** 也能把 Mansion 做到 `O(N)`——窗口右移时"减掉离开的、加上进来的"。
> 两种解法都满分，思路可以互相印证。

---

## 3. 一维前缀和 (1D Prefix Sum)

### 3.1 定义

设原数组为 `a[1], a[2], ..., a[N]`（**建议用 1-indexed，即下标从 1 开始**）。
定义前缀和表 (prefix sum table，又称累积和 cumulative sums / 部分和 partial sums)：

```
s[0] = 0
s[i] = a[1] + a[2] + ... + a[i]
```

递推写法：

```
s[i] = s[i-1] + a[i]
```

直观理解：`s[i]` 就是"从头到第 `i` 个元素的累加和"。

### 3.2 关键：任意区间的和 = 两个前缀之差

任意区间 `[l, r]` 的和：

```
sum(l, r) = a[l] + a[l+1] + ... + a[r] = s[r] - s[l-1]
```

用 ORAC 那张图的说法来理解：把你要求的区间想成**蓝色段**，
它等于**红色段**（从开头一直到 `r` 的前缀）**减去绿色段**（从开头到 `l-1` 的前缀）。
红、绿两段都是**前缀 (prefix)**，都能直接从前缀和表里查到——

```
s[r]   = a1 a2 ... a(l-1) | a(l) ... a(r)    ← 红色（前缀）
s[l-1] = a1 a2 ... a(l-1)                     ← 绿色（前缀）
蓝色   =                    a(l) ... a(r)      ← 相减剩下的正是所求区间
```

**核心洞察：数组里任意区间的和，都可以写成两个前缀和之差。**
所以只要预计算好所有前缀（`O(N)`），任意区间（不只是前缀）都能 `O(1)` 查询。

### 3.3 1-indexed 与哨兵 (sentinel)

当 `l = 1` 时，`s[l-1] = s[0] = 0`。我们把 `s[0]` 设为 0 当作**哨兵 (sentinel)**，
就不必为 `l = 1` 写特判。这是 1-indexed 的一大好处，能减少差一错误。

### 3.4 模板代码（多次区间查询）

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long a[MAXN];   // 原数组
long long s[MAXN];   // 前缀和表 (prefix sum table)

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 预计算 (precomputation)：O(n)
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
    }

    // 每次询问 (query)：O(1)
    while (q--) {
        int l, r;
        cin >> l >> r;
        long long ans = s[r] - s[l - 1];
        cout << ans << "\n";
    }

    return 0;
}
```

**口算验证**：`a = [3, 1, 4, 1, 5]`，则 `s = [0, 3, 4, 8, 9, 14]`。
`sum(2, 4) = s[4] - s[1] = 9 - 3 = 6`，即 `1 + 4 + 1 = 6`，正确。

### 3.5 回到 Mansion：把 50 分做成 100 分

长度为 `K` 的窗口，若右端点是 `i`（`i` 从 `K` 到 `N`），它覆盖 `a[i-K+1 .. i]`，
其和就是 `s[i] - s[i-K]`。枚举右端点取最大即可，总复杂度 `O(N)`：

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long a[MAXN];
long long s[MAXN];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    s[0] = 0;
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];

    long long best = -1;
    for (int i = k; i <= n; i++) {          // i 是窗口右端点
        long long windowSum = s[i] - s[i - k];   // a[i-k+1 .. i] 的和
        if (best == -1 || windowSum > best) best = windowSum;
    }

    cout << best << "\n";
    return 0;
}
```

对比一下：暴力是 `O(N·K)`（50 分），前缀和是 `O(N)`（100 分）。差别就在于把
"每个窗口现场求和"换成了"一次减法查表"。

> **小结（呼应 ORAC 原文）**：前缀和是一种可以在 `O(N)` 时间内构建、
> 之后能 `O(1)` 查询任意区间和的**数据结构 (data structure)**，是很多更复杂算法的基础模块 (building block)。

---

## 4. 差分数组 (Difference Array)：前缀和的逆运算

> 这一节 ORAC 前缀和页没有讲，但它是前缀和的"对偶"，AIO 常考，值得掌握。

前缀和解决"数组固定、反复查区间和"。它的逆运算叫**差分数组 (difference array)**，
解决相反的问题：**反复对区间做整体加减，最后才查询数组**。

### 4.1 问题

> 一个初始全为 0 的数组，进行 `M` 次操作，每次把区间 `[l, r]` 里所有元素都加上 `v`。
> 所有操作做完后，输出最终数组。

若每次真的循环去加，是 `O(N)` 一次、总共 `O(N·M)`，会超时 (TLE)。

### 4.2 做法

对每次"区间 `[l, r]` 加 `v`"，只改两个位置：

```
diff[l]   += v;
diff[r+1] -= v;
```

所有操作结束后，**对 `diff` 求一次前缀和 (prefix sum)，就还原出最终数组**：

```
a[i] = diff[1] + diff[2] + ... + diff[i]
```

理解：`diff[l] += v` 表示"从 `l` 开始多了 `v`"，`diff[r+1] -= v` 表示"从 `r+1` 起这个 `v` 又消失"。
求前缀和的过程，正好把这个"某处开始生效、某处结束"的效果累积出来。

> 一句话记忆：**前缀和 (prefix sum) 把"每点的值"变成"到此为止的累计"；
> 差分 (difference) 反过来，把"累计"拆回"每点的变化"。二者互为逆运算 (inverse operation)。**

### 4.3 代码

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long diff[MAXN];   // 差分数组，注意要能用到下标 r+1

int main() {
    int n, m;
    cin >> n >> m;

    for (int k = 0; k < m; k++) {
        int l, r;
        long long v;
        cin >> l >> r >> v;
        diff[l]     += v;
        diff[r + 1] -= v;
    }

    // 对差分数组求前缀和 = 还原最终数组
    long long cur = 0;
    for (int i = 1; i <= n; i++) {
        cur += diff[i];
        cout << cur << " ";
    }
    cout << "\n";

    return 0;
}
```

---

## 5. 二维前缀和 (2D Prefix Sum)

> 这一节 ORAC 前缀和页也没讲，但 AIO 常出网格 (grid) 题，务必掌握。

给一个 `N × M` 的矩阵，多次询问某个**子矩形 (subrectangle)** 内所有数的和。
一维前缀和可自然推广到二维。

### 5.1 定义

设矩阵 `a[i][j]`（`i` 行 `j` 列，都从 1 开始）。定义二维前缀和：

```
s[i][j] = 从 (1,1) 到 (i,j) 这个矩形内所有元素的总和
```

递推公式（用到**容斥原理 / Inclusion–Exclusion**）：

```
s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j]
```

为什么减 `s[i-1][j-1]`？因为上方那块 `s[i-1][j]` 和左方那块 `s[i][j-1]`
把左上角 `s[i-1][j-1]` **重复算了一次**，要减掉一次补偿。

```
    +----------------+
    |   s[i-1][j]    |   ← 上方一块
    |  +----------+  |
    |  |s[i-1][j-1]|  |   ← 被上方和左方重复覆盖
    +--+----------+  |
    |   s[i][j-1]    |   ← 左方一块
    +----------------+
```

### 5.2 查询任意子矩形的和

左上角 `(r1, c1)`、右下角 `(r2, c2)` 的子矩形之和：

```
sum = s[r2][c2]
    - s[r1-1][c2]      ← 减掉上面多出的横条
    - s[r2][c1-1]      ← 减掉左边多出的竖条
    + s[r1-1][c1-1]    ← 上、左都减掉了同一个左上小块，多减一次，补回来
```

同样是容斥 (inclusion–exclusion)：减两块、把多减的一块加回来。

### 5.3 代码

```cpp
#include <iostream>
using namespace std;

const int MAXN = 1005;
long long a[MAXN][MAXN];
long long s[MAXN][MAXN];

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    // 预计算二维前缀和：O(n*m)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];

    // 每次询问子矩形和：O(1)
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        long long ans = s[r2][c2] - s[r1-1][c2] - s[r2][c1-1] + s[r1-1][c1-1];
        cout << ans << "\n";
    }

    return 0;
}
```

因为用 1-indexed，`s[0][...]` 与 `s[...][0]` 天然是 0（全局数组默认清零），边界自动处理好了。

---

## 6. 家族成员：后缀和与前缀/后缀极值

前缀和只是一整类"扫描型预处理"的一员。它们的共同套路是：
**从一端往另一端扫，一边扫一边把当前的累计结果记下来。** 换一种"累计的运算"，就得到不同的工具。

### 6.1 后缀和 (Suffix Sum / Postfix Sum)

从右往左累加，`suf[i]` 表示 `a[i] + a[i+1] + ... + a[N]`：

```cpp
suf[n + 1] = 0;
for (int i = n; i >= 1; i--)
    suf[i] = suf[i + 1] + a[i];
```

用途：需要"某点右边所有元素之和"时，直接查 `suf[i]`。

### 6.2 前缀最大值 / 最小值 (Prefix Maxima / Prefix Minima)

`pmax[i]` 表示 `a[1..i]` 的最大值（不使用模板 `std::max`，用三目运算符更直观）：

```cpp
for (int i = 1; i <= n; i++) {
    if (i == 1) pmax[i] = a[i];
    else        pmax[i] = (pmax[i-1] > a[i]) ? pmax[i-1] : a[i];
}
```

求前缀最小值 (prefix minima) 把 `>` 改成 `<` 即可。

### 6.3 后缀最大值 / 最小值 (Suffix Maxima / Suffix Minima)

`smax[i]` 表示 `a[i..n]` 的最大值，从右往左扫：

```cpp
for (int i = n; i >= 1; i--) {
    if (i == n) smax[i] = a[i];
    else        smax[i] = (smax[i+1] > a[i]) ? smax[i+1] : a[i];
}
```

这些统称"扫描前缀/后缀信息"，在 AIO 里常与前缀和搭配，尤其是
"对每个位置，我想知道它**左边的最好情况 / 右边的最好情况**"这类题。

---

## 7. 关键区别：可逆 vs 不可逆

这是很多同学忽略、但对做题极关键的一点，请重点理解：

- 前缀**和 (sum)** 能回答**任意区间** `[l, r]`，靠的是 `s[r] - s[l-1]`。
  这里用到**减法**，也就是加法的**逆运算 (inverse operation)**。因为加法可逆，
  才能"把前面不要的那段减掉"。
- 前缀**最大值 (maxima)** 做不到。`max` **没有逆运算**——
  你无法从 `max(a[1..r])` 里"去掉" `max(a[1..l-1])` 的影响。
  所以 `pmax` 只能回答"从头到某处"（前缀区间），`smax` 只能回答"从某处到末尾"（后缀区间）。

**结论**：
- 求和、异或 (XOR) 这类**可逆**运算 → 能做**任意区间**查询。
- 求最大 (max)、最小 (min)、gcd 这类**不可逆**运算 → 前缀/后缀数组只能查"带一个固定端点"的区间。
  要查**任意区间的最大/最小值**，需要更高级的结构（稀疏表 Sparse Table、线段树 Segment Tree），那是以后的内容。

在只学到前缀和的阶段，遇到"任意区间最大值"先别慌——很多题其实只需要"前缀最大"或"后缀最大"，
端点固定在两头，用扫描就够了。

---

## 8. 综合例题

### 例题 A：最平衡的分割点（前缀和 + 总和）

> 把数组从某处切成左右两半，使**左半和与右半和之差的绝对值最小**，输出这个最小差值。

左半和是 `s[i]`，右半和是 `总和 - s[i]`，枚举切点即可：

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long a[MAXN];
long long s[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];

    long long total = s[n];
    long long best = -1;
    int bestPos = 0;

    for (int i = 1; i < n; i++) {          // 在第 i 和第 i+1 个之间切
        long long leftSum  = s[i];
        long long rightSum = total - s[i];
        long long d = leftSum - rightSum;
        if (d < 0) d = -d;                 // 取绝对值
        if (best == -1 || d < best) {
            best = d;
            bestPos = i;
        }
    }

    cout << "在第 " << bestPos << " 个元素后切，最小差值 = " << best << "\n";
    return 0;
}
```

### 例题 B：接雨水（前缀最大 + 后缀最大配合）

> 给一排柱子高度 `h[1..N]`，位置 `i` 能积的水 = min(它左边最高柱, 它右边最高柱) − `h[i]`。求总积水量。

"左边最好情况 = 前缀最大 (prefix maxima)，右边最好情况 = 后缀最大 (suffix maxima)"的经典配合：

```cpp
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long h[MAXN];
long long pmax[MAXN];   // 前缀最大 (prefix maxima)
long long smax[MAXN];   // 后缀最大 (suffix maxima)

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];

    for (int i = 1; i <= n; i++)
        pmax[i] = (i == 1) ? h[i] : (pmax[i-1] > h[i] ? pmax[i-1] : h[i]);

    for (int i = n; i >= 1; i--)
        smax[i] = (i == n) ? h[i] : (smax[i+1] > h[i] ? smax[i+1] : h[i]);

    long long total = 0;
    for (int i = 1; i <= n; i++) {
        long long left  = pmax[i];
        long long right = smax[i];
        long long lower = (left < right) ? left : right;   // 两边较矮者决定水位
        total += lower - h[i];    // pmax[i] 已含 h[i]，故不会为负
    }

    cout << total << "\n";
    return 0;
}
```

### 例题 C：二维子矩形统计（二维前缀和）

题面就是第 5 节的模板：给网格，多次问某子矩形的和。常见变体：网格是 0/1，问某矩形里有多少个 1。
本质都是二维前缀和 + `O(1)` 查询。

> **拓展思路（前缀积 × 后缀积）**：若要"对每个位置求除它以外所有数的乘积"、又不许用除法，
> 可用前缀积和后缀积：`ans[i] = 前缀积[i-1] × 后缀积[i+1]`。这和"前缀最大 × 后缀最大"是同一种
> "把左右信息拼起来"的套路。

---

## 9. 常见坑与注意事项

1. **溢出 (overflow)**：前缀和越加越大，`int` 容易爆（超过约 21 亿）。**前缀和数组一律用 `long long`**。
2. **下标越界**：一维差分要用 `diff[r+1]`，数组开到 `n+2`；二维前缀和会访问 `s[0][j]`、`s[i][0]`，第 0 行/列要存在。
3. **初始化 `s[0]=0`**：全局数组自动清零；局部数组或多组数据复用时记得手动清零。
4. **坚持 1-indexed**：`s[0]=0` 当哨兵，能消掉大半边界特判；别混用 0-indexed 和 1-indexed。
5. **分清"查询型"和"更新型"**：数组不变、反复查区间和 → 前缀和；反复区间整体加、最后看结果 → 差分。
6. **不可逆运算别硬套任意区间查询**：任意区间的 max/min 需要以后学的稀疏表 / 线段树。

---

## 10. 复杂度速查表

| 技术 | 预处理 | 单次查询 / 更新 | 典型用途 |
|------|--------|-----------------|----------|
| 一维前缀和 (1D Prefix Sum) | `O(n)` | 查询 `O(1)` | 任意区间求和 |
| 差分数组 (Difference Array) | 每次更新 `O(1)` | 最后还原 `O(n)` | 反复区间整体加减 |
| 二维前缀和 (2D Prefix Sum) | `O(n·m)` | 查询 `O(1)` | 子矩形求和 |
| 前缀/后缀极值 (Prefix/Suffix Extrema) | `O(n)` | 查询 `O(1)` | 带固定端点的区间极值 |

朴素区间求和是查询 `O(n)`；前缀和把总复杂度从 `O(n·q)` 降到 `O(n + q)`，
这往往就是能否通过 (AC) 的分水岭。

---

## 11. AIO 练习题（ORAC 链接）

跟着 ORAC 的路线练手（**先自己想至少 15 分钟再看题解**）：

1. **Mansion (AIO 2007)** — 前缀和入门题，把本教程第 2、3 节直接用上。
   题目：<https://orac.amt.edu.au/problem/aio07mansionsen/>
2. **Alien (AIO 2011)** — ORAC 的进阶练习。提示：找"发射位置"和 Mansion 找"最佳区间"很像，
   想想能不能**先把输入变形**，再套 Mansion 的思路。
   题目：<https://orac.amt.edu.au/problem/aio11aliens/>
3. **Two Pointers / 滑动窗口教程** — Mansion 的另一种 `O(N)` 解法，和前缀和互相印证。
   教程：<https://orac.amt.edu.au/hub/train/aio-twopointers>
4. **Backpacking (AIO 2024) 题解** — 展示前缀和如何作为更复杂算法的一个模块。
   题解：<https://orac.amt.edu.au/hub/train/editorials-aio24-q4>

练习方法建议：先默写一维/二维前缀和与差分三份模板并手算验证；做题时训练"识别信号"——
"多次区间和"→前缀和；"网格子矩形统计"→二维前缀和；"很多次区间加、最后输出"→差分；
"每个位置左/右的最大或最小值"→前缀/后缀极值。

> ORAC 训练总入口：<https://orac.amt.edu.au/hub/train/aio>

---

> 掌握前缀和、差分、二维前缀和、前缀/后缀极值这一套"扫描型预处理"，
> 你在 AIO 里就能稳稳吃下一大类区间统计题。等以后学了动态规划和线段树，
> 你会发现前缀和的思想（"把重复计算提前算好、存起来复用"）无处不在。
