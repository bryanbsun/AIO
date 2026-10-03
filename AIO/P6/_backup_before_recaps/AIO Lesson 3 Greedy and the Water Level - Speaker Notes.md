# AIO High Achievers Camp · Session 3: Greedy and the Water Level

## 演讲者备注（Speaker Notes）

每页的备注与本次课 slides 中的 speaker notes 相同；课堂练习的答案都写在对应页的备注里。页码与 AIO Lesson 3 Greedy and the Water Level.pptx 一致。

**第 1 页 · Greedy and the Water Level**

第 3 次课：三道题画出来是同一幅图，一排柱子和一条水平线。两道题削掉线上方的峰（cut the peaks），一道题填平线下方的谷（fill the valleys）。其中两道用 Binary Search 找这条线，第三道枚举每一个值。

**第 2 页 · Today's plan**

Wheeling and Dealing 的完整解法需要 Fenwick tree（BIT）。课上讲思路和手算即可，BIT 的实现作为选读。

**第 3 页 · Guess a rule, then prove it is safe**

没有第 3 步的 Greedy 规则只是猜测。AIO 的题通常猜规则很容易，证明才是真正的工作。整节课把第 3 步留在黑板上。

**第 4 页 · Columns and a water level**

整节课都把这幅图留在黑板上。每道题都问：柱子是什么？这条线代表什么？
参考：Mundane Square：柱子 = 每列还缺的数量，线 = λ（削峰）；Wheeling and Dealing：柱子 = 每个对手的票数，线 = k − 1（削峰）；Prime Minister：柱子 = 右半边每个人的财富，线 = x（填谷）。

**第 5 页 · Mundane Square**

约 35 分钟。这是本次课的核心题，另外两道都拿来和它比较。

**第 6 页 · The problem**

在黑板上写样例 1：K = 4，R = 6 8 3，C = 5 5 7。

**第 7 页 · Necessary, but not enough**

提到 max-flow 只是让较强的学生知道这题在理论上属于哪一类，课上不讲。

**第 8 页 · Fill row by row: tallest column first**

这是 Greedy 三步法的第 1 步：猜规则。下一页是第 3 步：exchange argument。

**第 9 页 · The exchange argument**

在右侧画一个 2×2 的子网格：当前行和第 r 行、第 i 列和第 j 列，四个格子分别标 +1/−1。K = 1 时这就是 Gale–Ryser 定理背后的构造。这份解答也用 max-flow 暴力对拍验证过。

**第 10 页 · Water-filling: binary search the level**

指回水位线图的左半边：这就是"削峰"。上限 K 表示每一格最多削 K。

**第 11 页 · For each row**

第 2 步常被误解：capacity 是这一行最多能发出多少（每格 ≤ K，也不超过该列还缺的数量）。如果连这个都小于 R[i]，这一行就填不满；如果 ≥ R[i]，说明有余量，由 λ 决定少发多少。

**第 12 页 · Sample 1, row 1 (send 6)**

答案：λ = 3：2 2 4 = 8 > 6。λ = 4：1 1 3 = 5 ≤ 6。所以 λ = 4，零头 leftover = 1，给第 1 列（5 − 1 = 4 = λ，且 1 < K）。第 1 行 = 2 1 3，rem = 3 4 4。
第 2 行（发 8）：λ = 0 得 11，λ = 1 得 2 3 3 = 8 → 第 2 行 = 2 3 3，rem = 1 1 1。
第 3 行（发 3）：1 1 1。输出 YES / 2 1 3 / 2 3 3 / 1 1 1（和样例输出不同，但题目接受任何合法的矩阵）。

**第 13 页 · give(λ) and the search**

l 从 0 开始，r 取 rem[j] 的最大值。N 行 × 约 30 次二分 × N 列 ≈ 3×10^7，没问题。最多要输出 10^6 个数：每行结束时用一次 endl，不要每个数都 endl。

**第 14 页 · Subtasks and common mistakes**

提问：如果每个格子有自己的上限 K[i][j]，Greedy 还成立吗？
答案：不一定，这时需要真正的 max-flow。

**第 15 页 · Wheeling and Dealing**

约 20 分钟。注意这里不用 Binary Search：花费关于水位线不单调，这是和 Mundane Square 最主要的区别。

**第 16 页 · The problem**

所以唯一的问题是：买哪些选民？
参考：让被买的选民都改投 1 号（对手少一票、1 号多一票），一定不比改投别人差。

**第 17 页 · Fix our final vote count k**

Exchange argument：如果买了某个对手较贵的选民，却没买他更便宜的选民，换成便宜的，票数结果相同，花费更少。

**第 18 页 · A small example**

答案（自编例子，已用解答程序验证）：
k = 1：两个对手都削到 0：1+2+5+9 + 3+3 = 23，我方 7 票。
k = 2：2 号削到 1（1+2+5），3 号削到 1（3）= 11，我方 5 票。
k = 3：2 号削到 2（1+2）= 3，我方 3 票。最优。
k = 4：2 号削到 3（1），我方 2 票，再补买剩下最便宜的 2 个（2+3）= 6。
k = 5：不用削，补买最便宜的 4 个（1+2+3+3）= 9。
花费依次是 23、11、3、6、9：两头都贵，关于 k 不单调，所以不能二分，只能枚举每个 k。

**第 19 页 · Same picture, different search**

提问：为什么 Mundane 可以二分水位线，而 Wheeling 不行？
答案：指着花费 23、11、3、6、9：Wheeling 的花费关于 k 不单调；Mundane 中"这一行发出的总量"关于 λ 单调不增。

**第 20 页 · Sweep k from high to low**

Fenwick tree 超出了本课程的核心内容。Subtask 1–2（每个花费都是 $1）只需要计数；subtask 3（N, M ≤ 100）可以对每个 k 直接重算。和 Codeforces 1019A "Elections" 是同一类题。

**第 21 页 · Prime Minister**

约 20 分钟，之后这道题就是现场编码题。

**第 22 页 · The problem**

在黑板上写样例 1：N = 5，K = 4，A = 1 2 5 6 9。答案 7。

**第 23 页 · Can the median reach x?**

搜索范围：[A[md], A[md] + K]。
提问：为什么 A[md] + K 是安全的上界？
答案：中位数要 ≥ x，至少要让 A[md] 这个人达到 x；就算把 K 全给他，也只能到 A[md] + K。

**第 24 页 · Sample 1: K = 4, A = 1 2 5 6 9**

答案：md = 3，右半边 5 6 9，搜索范围 [5, 9]。
x = 6：要补 1 0 0 → 1，可以。x = 7：2 1 0 → 3，可以。x = 8：3 2 0 → 5，不行。答案 7（找最后一个可行值 → 输出 r）。

**第 25 页 · Three uses of the water level**

和全班一起填这张表，一次填一列。
参考答案就是表中内容：柱子分别是右半边的财富 / 每列还缺的数量 / 每个对手的票数；动作分别是填谷 / 削峰（每格 ≤ K）/ 削峰；找水位线的方法分别是二分（最后一个 x）/ 二分（第一个 λ）/ 枚举每个 k；目标分别是最优化 / 判断有没有解并构造 / 最优化。

**第 26 页 · One min, one max apart**

提问：两个函数分别朝哪个方向单调？分别找第一个还是最后一个可行值？
答案：Prime Minister：x 越大 cost 越大，找最后一个可行的 x（→ r）。Mundane：λ 越小 give 越大，找第一个满足 give(λ) ≤ R[i] 的 λ（→ l）。

**第 27 页 · Write Prime Minister from scratch**

常见 bug：给整个数组补钱，而不是只补右半边；int 溢出（A[md] + K 可达 2×10^9）；输出 l 而不是 r。
样例答案：7、6、2。

**第 28 页 · Techniques used so far**

指出：到目前为止 9 道题中有 6 道用了 Binary Search。下次课会加一个新工具 Sparse Table，以及整个课程最难的题。

**第 29 页 · Homework**

下次课：Sparse Table、Robot Writing 和 Beach Umbrellas。
第 3 题参考答案：如果每格上限 K[i][j] 不同，"优先给需求最大的列"就不一定对了（某些列在某些行的上限很小），一般需要 max-flow。
