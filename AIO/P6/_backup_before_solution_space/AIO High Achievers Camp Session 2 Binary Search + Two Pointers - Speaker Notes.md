# AIO High Achievers Camp · Session 2: Binary Search + Two Pointers

## 演讲者备注（Speaker Notes）

每页的备注与本次课 slides 中的 speaker notes 相同；课堂练习的答案都写在对应页的备注里。页码与 AIO High Achievers Camp Session 2 Binary Search + Two Pointers.pptx 一致。

**第 1 页 · Binary Search + Two Pointers**

第 2 次课的主题是单调性（monotonicity）：它从哪里来，Binary Search 和 Two Pointers 怎样利用它。今天有三种来源：题目直接给的（Laser Cutter）、用前缀最小值造出来的（Space Mission）、用总和造出来的（Lollipops II）。

**第 2 页 · Today's plan**

先用 5 分钟讲上次的作业（Tennis Robot II）：谁的轮数除法公式写对了？
参考：t = (s − 1) / (−d[i]) + 1，其中 s = X[i] + mn[i]；s < 1 时 t = 0；d[i] ≥ 0 时跳过。

**第 3 页 · Today: the monotone pair**

今天每道题都问同一个问题：单调性从哪里来？是题目给的，还是我们自己造出来的？

**第 4 页 · The while (l <= r) template**

这和课程里 timber、expense 题用的是同一个模板。
提问："能放下的最大正方形"用哪个写法？答案：找最后一个可行值 → 输出 r。
"总和达到 S 的最小半径"用哪个写法？答案：找第一个可行值 → 输出 l。

**第 5 页 · Laser Cutter**

约 30 分钟。这里的单调性是题目直接给的：两条切割线都是阶梯（staircase）。

**第 6 页 · The problem**

在右侧画样例 2：A = DDDDDDRRRRRR（先下后右），B = RDRRDDDRRRDD。答案是 3。

**第 7 页 · Brute force, and why it fails**

Brute force 仍然值得写：它能拿 N ≤ 10 和 N ≤ 1000 的 subtask 分，之后还能当对拍用的 checker。

**第 8 页 · Describe the shape column by column**

单调性就是从这里来的，而且是题目直接给的。画一列，标出 yb 和 ya。
参考（样例 2）：ya = 6 6 6 6 6 6，yb = 0 1 1 4 4 4，两者都单调不减。

**第 9 页 · Does an s×s square fit at columns x … x+s−1?**

常见错误：在同一列里同时检查上下边界。画图说明：最右一列限制顶边，最左一列限制底边（因为 yb、ya 都单调不减）。

**第 10 页 · Sample 2**

答案：ya = 6 6 6 6 6 6，yb = 0 1 1 4 4 4。
s = 3，x = 1：6 − yb[3] = 6 − 1 = 5 ≥ 3，放得下。
s = 4：x = 1：6 − yb[4] = 2；x = 2：6 − yb[5] = 2；x = 3：6 − yb[6] = 2。都放不下。答案 3。

**第 11 页 · trace() and check(s)**

复杂度 O(N log N)。二分就是模板页右侧"找最后一个可行值"的写法，l = 1，r = n，输出 r。

**第 12 页 · Subtasks and common mistakes**

挑战：能不能不用 Binary Search？
答案：设 g(x) 为从第 x 列开始能放下的最大正方形边长，可以证明 g(x+1) ≥ g(x) − 1，所以用一个只往前走的指针就能在 O(N) 内求出所有 g(x)。这就是 Two Pointers 版本。

**第 13 页 · Space Mission**

约 20 分钟。和 Laser Cutter 对比：那里的阶梯是题目给的；这里要自己造出单调性。

**第 14 页 · The problem**

提问：固定返回日 j，我们想要哪个出发日？
答案：最靠左的 i，满足 C[i] ≤ F − C[j]。

**第 15 页 · Ask a monotone question instead**

前缀最小值（prefix minimum）是 prefix sum 的"min 版本"：两者都是把前 i 个数合起来。这时可以强调"单调性是我们自己造出来的"。

**第 16 页 · Sample 2: F = 14**

答案：pm = 12 8 2 2 2 2 2。
j = 6：need = 8 → 第一个 pm ≤ 8 的是 i = 2 → 5 天。
j = 7：need = 4 → i = 3 → 5 天。
j = 4：need = −2 → 找不到。
答案 5。

**第 17 页 · Prefix minimum, then one search per j**

ans 初始化为 −1。复杂度 O(N log N)。这是后面的现场编码题，先不要发代码。

**第 18 页 · Two ways to use binary search**

挑战：Space Mission 能不能用 Two Pointers 做到 O(N)？
答案：最优的出发日 i 一定是"前缀最小值创新低"的那一天，最优的返回日 j 一定是"后缀最小值"的那一天。把这两组位置分别列出来：i 往右走时 C[i] 变小，允许的 C[j] 上限 F − C[i] 变大，能用的最远 j 只会往右移，所以一个指针扫一遍即可，O(N)。

**第 19 页 · Lollipops, Sweets and Chocolates II**

约 30 分钟。今天最难的"自己造单调性"。

**第 20 页 · The problem**

在数轴上画样例 1：商店 1 5 8 9，房子 3 6 8 10 14。

**第 21 页 · Too many values of R**

Subtask 2–4：只有商店和房子之间的距离会改变某个计数，所以只有约 N·M 个"有意义的"R，逐个检查就能拿这些 subtask。

**第 22 页 · Find the monotone quantity**

观察 2 是一个很好的小证明：如果每个数都不变小，那么排序后第 k 小的数也不会变小。
观察 3：每个位置都 ≤，总和又相等，所以每个位置都相等。

**第 23 页 · If that R fails, every R fails**

这就是"先用总和过滤"的想法。样例 2 很好地说明了这一点：总和从 3 直接跳到 5，永远等不到 4。

**第 24 页 · Two Pointers for every count**

在题目页的数轴上画出滑动窗口。
参考（样例 1，R = 3）：房子 3 → [0, 6] 内的商店 1、5，计数 2；房子 6 → [3, 9] 内 5、8、9，计数 3；房子 8 → 3；房子 10 → [7, 13] 内 8、9，计数 2；房子 14 → 0。总和 10。

**第 25 页 · Sample 1: S = 10**

答案：R = 2：2 2 2 2 0，总和 8。R = 3：2 3 3 2 0，总和 10。最小的 R 是 3；排序后 0 2 2 3 3 = s；答案 3（R = 4 得到同样的向量，也被接受，正好印证观察 3）。
样例 2：商店 1 3 5，房子 2 6，s = 1 3（S = 4）。R = 2 总和 3，R = 3 总和 5：总和永远不等于 4，输出 −1。

**第 26 页 · total(R) and the search**

注意边界：<= ho[i] + R，但 < ho[i] − R，一个等号写错就会出错。总和用 long long（最大 M × N = 10^10）。

**第 27 页 · Where does the monotonicity come from?**

先让学生填右边一列，再显示答案。
参考答案：Laser Cutter：本身就是单调的阶梯，题目给的；Space Mission：花费数组 C 不单调 → 前缀最小值 pm 单调，我们造的；Lollipops II："排序后的计数等于 s"不单调 → 计数总和单调，我们造的。

**第 28 页 · Write Space Mission from scratch**

常见 bug：在 pm[1..j] 上搜索，而不是 pm[1..j−1]（出发日和返回日必须不同）；忘了输出 −1；F − C[j] 用 int 不会溢出，但为了保险还是用 long long。
样例答案：样例 1 = 4，样例 2 = 5，样例 3 = −1。

**第 29 页 · Techniques used so far**

这张表每次课都会变长。Greedy 那一列现在还几乎是空的：那是第 3 次课的内容。

**第 30 页 · Homework**

下次课：Greedy 和水位线（water level）。提醒学生把 binary search 模板留在手边，下次每道题都会用到。
