# AIO High Achievers Camp · Session 4: Sparse Table + Greedy

## 演讲者备注（Speaker Notes）

每页的备注与本次课 slides 中的 speaker notes 相同；课堂练习的答案都写在对应页的备注里。页码与 AIO Lesson 4 Sparse Table + Greedy.pptx 一致。

**第 1 页 · Sparse Table + Greedy**

第 4 次课，也是最后一次课。一个新工具：Sparse Table（O(1) 求区间 min / max），用在 Ladybugs II 和 Robot Writing。然后是整个课程最难的 Beach Umbrellas，重点讲 Greedy 的想法和 subtask 台阶。

**第 2 页 · Today's plan**

Beach Umbrellas 是整个课程最难的题。今天讲 Greedy 的想法和到 subtask 4 为止的台阶；完整的 binary lifting 解法给强的学生课后阅读。Yet Another Lights（2023 P6）课上不讲：它是奇偶性（parity）构造题，放在作业页作为选读。

**第 3 页 · Today: all four, plus one tool**

这是第 1 次课的"三问"。在给出 key observation 之前，让全班针对今天每道题大声回答。
参考答案：
Ladybugs II：brute force 是每个询问枚举所有窗口 O(QN)；位置已排序 → Binary Search 定位 D；f1、f2 只和窗口有关，可以预处理 → Sparse Table。
Robot Writing：brute force 是枚举起点和每一步方向 2^M；机器人脚下的值单调不减；区域边界可以用 Binary Search + Sparse Table 找。
Beach Umbrellas：brute force 是枚举左端点再 Greedy 模拟 O(N·K)；每把伞的放法可以局部决定（Greedy）；X = 1 时可以用 Two Pointers。

**第 4 页 · Max of any range in O(1)**

答案：sp[1] = 3 4 4 5 9 9 6。sp[2] = 4 5 9 9 9。
查询 [2, 7]：长度 6，k = 2（≤ 6 的最大 2 的幂是 4）。max(sp[2][2], sp[2][4]) = max(5, 9) = 9。
要点：两个长度为 4 的块有重叠（位置 4、5 被算了两次）。对 max 和 min 没关系，但对求和不行：所以求和要用 prefix sum。
预处理 O(N log N)，查询 O(1)。数组不能被修改。

**第 5 页 · Build once, ask many times**

2^17 = 131072 > 10^5，17 层就够了，开 20 层更保险。lg[1] = 0，因为全局数组初始为 0。求区间最小值时把 max 改成 min。和 prefix sum 对比：两者都是"先预处理，再快速回答每个区间问题"。

**第 6 页 · Ladybugs II**

约 25 分钟。第一次用 Sparse Table。这里的 Two Pointers 指的是"K 个连续元素组成的滑动窗口"这个想法。

**第 7 页 · The problem**

在右侧画数轴，标出 P = 1、4、6（样例 1），K = 2。再标出三个询问 D = 0、5、2。

**第 8 页 · The K ladybugs are always consecutive**

先问：为什么一定是连续的？让学生在数轴上论证。
答案：在一条线上从最左走到最右，中间的瓢虫都会被经过，签名白拿；所以只要有更远的瓢虫被选上，中间的就可以换进来而不增加时间。
和今天后面的 Beach Umbrellas 呼应：那里的答案也是一整段连续区间。

**第 9 页 · Three kinds of window**

前两种情况各 O(1)。第三种是难点：每个询问最多 K − 1 个窗口，Q 个询问，K 和 Q 都大时太慢。
提问：有多慢？答案：Q × K，例如 10^10。

**第 10 页 · Pull D out of the formula**

这是本题最重要的想法：只和窗口有关的量都可以预处理。和 prefix sum 是同一种思路：把不依赖询问的部分先算好。

**第 11 页 · Sample 1**

答案：
D = 0：s = 1。全在右边：l = 1，4 − 0 = 4。没有全在左边的，也没有跨过 D 的。答案 4。
D = 5：s = 3。全在右边：无。全在左边：以第 2 只结尾的窗口 [1, 4]，5 − 1 = 4。跨过 D：l = 2（[4, 6]）：2 + min(1, 1) = 3。答案 3。
D = 2：s = 2。全在右边：l = 2，6 − 2 = 4。全在左边：无。跨过 D：l = 1（[1, 4]）：3 + min(1, 2) = 4。答案 4。
期望输出：4 3 4。

**第 12 页 · Precompute, then answer**

用 long long。每个询问：一次 Binary Search O(log N)，加上三种情况各 O(1)。Subtask 台阶：Q = 1 → 枚举所有窗口；K = N → 只有一个窗口；完整 → Binary Search + Sparse Table。

**第 13 页 · Robot Writing**

约 30 分钟。这里的 "Greedy" 指的是一个 Greedy 风格的 key observation（机器人最后总是拿着较大的值），而不是我们做的某个贪心选择。

**第 14 页 · The problem**

Brute force：枚举起点和每一步的方向，2^M 种，只能过极小的 subtask。我们需要弄清楚交换到底做了什么。

**第 15 页 · Simulate sample 1**

答案：
第 1 步：在格子 3，记录 1，移到 4（值 2），2 > 1 不交换，T = 2 3 1 2 3。
第 2 步：在格子 4，记录 2，移到 3（值 1），1 < 2 交换，T = 2 3 2 1 3。
第 3 步：在格子 3，记录 2，移到 2（值 3），不交换，T = 2 3 2 1 3。
第 4 步：在格子 2，记录 3。
记录下来的是 1 2 2 3 = S，所以 YES。
要注意到的规律：机器人脚下的值从来不会变小。

**第 16 页 · The robot carries the maximum**

这一行就把题目里所有的交换都消掉了。较小的值被推到机器人身后，之后再也不重要。Greedy 的味道：机器人总是留下较大的那个数。

**第 17 页 · Trapped in a region**

在右侧把 T 画成柱子，在 v 处画一条水平线：区域就是线下方的那段谷。和第 3 次课的水位线图对比。找左端点：最小的 l 使 max(T[l..p]) ≤ v，这关于 l 单调，所以用 Binary Search + Sparse Table。

**第 18 页 · Arrive exactly on time**

这个奇偶性论证在很多网格题里都出现过（2019 P5 Evading Capture 也用到奇偶距离）。
提问：为什么第一次升级之后，区域总是至少有 2 格？
答案：新区域包含原来的区域加上新踩上的那一格。

**第 19 页 · Layer by layer**

答案（样例 2）：
值 2，第 1 步首次出现：格子 2，区域 [1, 2]（2 格，OK）。
值 3，第 4 步首次出现：目标格子 3（区域右侧，值 3 ✓），d = 1，dt = 3，3 − 1 = 2 是偶数 ✓。区域变成 [1, 3]。
值 4，第 5 步首次出现：目标格子 4（值 4 ✓），d = 1，dt = 1 ✓。
最后一层之后在区域内来回走即可。YES。
样例 3：起点格子 1，区域 [1, 1] 只有 1 格，第 2 步必须离开，记录到 2。NO。

**第 20 页 · Two small helpers**

主循环：把 S 分成若干层（值 lv[k]，首次出现的步数 ti[k]；不要叫 tm，会和系统里的名字冲突）。维护当前层所有可能的位置；对每个位置用 extendLeft/extendRight 求出 [l, r]，检查 l − 1 和 r + 1 两个格子，合格的加入下一层（用 mark[] 去重）。每个格子最多出现在一层里，所以总复杂度 O((N + M) log N)。
常见错误：只要目标格子比 v 大就接受；必须恰好等于新的值。

**第 21 页 · Beach Umbrellas**

约 25 分钟。整个课程最难的题。今天的目标：Greedy 的想法、反例，以及一条清楚的通往 subtask 4 的路线。完整解法作为课后阅读。

**第 22 页 · The problem**

相邻也要合并：[2, 4] 和 [5, 6] 合并成 [2, 6]。K × X 可达 10^18，要用 long long。Subtask 1（K = 0）就是合并区间后找最长的 block。

**第 23 页 · Fill each gap separately?**

已覆盖的 block 是 [4]、[6, 7]、[9, 10]。让全班在空白行里放 2 把伞。
错误想法：gap {3}、{5}、{8} 各需要 1 把伞；2 把伞最多连起两个 gap，例如 3..7 或 4..10，长度 7。
正确做法：一把伞放 3–5（跨过格子 4，同时盖住 gap 3 和 gap 5），另一把放 8–10。覆盖 3..10，长度 8。
当 X = 1 时（subtask 2），按 gap 分开算是对的：伞不可能跨过任何东西。这就是用 Two Pointers 的 subtask。

**第 24 页 · Fix the left end l**

这是经典的区间覆盖（interval covering）Greedy。一句话的 exchange argument：把任何一把伞移到左端贴住第一个未覆盖的格子，覆盖段只会变长。这个 brute force 留着做对拍。

**第 25 页 · Where should l be?**

答案：
l = 4：伞放 6–7、8–9、10（第三把被海滩尽头截断，只盖 1 格）。4..10，长度 7。
l = 1：伞放 1–2、3，接上 block，再放 6–7。1..7，长度 7。
最优：伞放 2–3、6–7、8–9 → 2..9，长度 8。最优的左端 2 在 gap 的中间！
结论："从 1 或从某个 block 开始"听起来对，其实是错的。右边被海滩尽头浪费了半把伞，不如把它放到左边。

**第 26 页 · Slide left until you touch a block**

用反例验证：B = [4, 5]，st_B = 4，X = 2，i = 1 得到 l = 2，正是我们找到的最优答案。和第 3 次课一样的 Greedy 三步法：猜规则，取一个违反规则的最优解，平移 / 交换说明它不会更差。

**第 27 页 · Right side first, unless the beach ends**

如果 K 把伞从 B 出发都到不了 N，就全部放右边。第二种方案避免浪费最后那把会在 N 处被截断的伞（正是反例里发生的情况）。这样候选从 O(U · K) 减少到 O(U)。

**第 28 页 · How far do j umbrellas go?**

只给强的学生。第 2 步的做法：从右往左扫描所有 block，用一棵按"模 X 的余数"建的线段树（segment tree），每个 block 覆盖一段余数。Binary lifting 和 Sparse Table 是同一种倍增思想：sp[k] 覆盖 2^k 个格子，up[p] 覆盖 2^p 次跳转。完整代码：P6 文件夹里的 2020_P6_Beach_Umbrellas.cpp。

**第 29 页 · The subtask ladder**

比赛建议：subtask 1–4 只用到今天讲的想法，而且分值占很大比重。先拿稳它们，再去追完整解法。
常见错误：按 gap 分开算 ceil(g / X)；只尝试 block 的起点；伞超出 N；忘了合并相邻的区间；int 溢出。

**第 30 页 · Write Ladybugs II**

常见 bug：跨过 D 的区间 lo/hi 差一（lo = max(1, s − K + 1)，hi = min(s − 1, w)）；忘了 s = N + 1 的情况（D 在所有瓢虫右边）；2 * p 用 int 溢出；sp 数组开小了。
样例答案：4 3 4。

**第 31 页 · Twelve problems, four techniques**

按列读，而不是按行读：12 道题中 Binary Search 出现 8 次，Greedy 6 次，Prefix Sum 5 次。几乎每道 P6 都要先有一个 key observation，再用一到两个核心技巧。让每个学生选一行，用 30 秒讲清楚。

**第 32 页 · Homework**

Yet Another Lights 不用四大技巧中的任何一个：它考的是奇偶性（parity）和不变量（invariant）。适合喜欢数学的学生。完整讲解见教学讲义第 13 节。
