# AIO 第 5、6 题课程：演讲者备注

每页的备注与 slides 中的 speaker notes 相同；课堂练习的答案都写在对应页的备注里。

## AIO Lesson 1: Prefix Sum

**第 1 页 · Prefix Sum**

这一系列共 4 次课，每次约 2 小时。贯穿全部课程的主线是 AMT 的四大核心技巧：Prefix Sum、Binary Search、Two Pointers 和 Greedy。  
第 1 次课讲 Prefix Sum：先讲普通的 prefix sum，再讲"一轮的净变化"（net change per round），最后讲二阶差分（second-order differences）。

**第 2 页 · AMT's four core techniques**

四种颜色在 4 次课里保持不变：青色 = Prefix Sum，橙色 = Binary Search，珊瑚红 = Two Pointers，深蓝 = Greedy。每道题开始时都先标出它用到哪几个技巧。

**第 3 页 · Three questions**

强调：P6 很少是"直接套模板"。四大技巧只是骨架，真正的难点是找到 key observation，把题目化简到能套模板为止。右侧空白用来写学生的回答。  
参考答案（以今天的题为例）：  
1. Brute force：Spaceship 枚举每条边的流量；Tennis 直接模拟（可达 2×10^11 步）；Twin Rivers 枚举新桥位置 p 再重算所有行程，O(L·T)。  
2. 单调的量：Tennis 中每个箱子的球数随轮数线性变化；Twin Rivers 中桥的位置已排序，可以 Binary Search 找最近的桥。  
3. 可累加 / 局部决定的量：Spaceship 的边流量是 prefix sum；Tennis 的一轮净变化是 prefix sum；Twin Rivers 的总代价可用二阶差分累加。

**第 4 页 · One technique per session**

每道 Problem 5 都和同一次课的一道 Problem 6 配对：核心想法相同，化简步骤更短，用来巩固。

**第 5 页 · Spaceship Shuffle**

约 30 分钟。讲解路线：把环剪成链（纯 prefix sum）→ 回到环（多一个变量 f）→ 中位数（median）。

**第 6 页 · The problem**

提问：为什么只看净流量（net flow）？  
答案：如果同一条边上有人往左、有人往右，让他们互换身份，花费只会减少。所以最优解里每条边只有一个方向。  
右侧空白可以画一个 6 个 cabin 的环。

**第 7 页 · Cut the ring into a chain**

在黑板上画链 5 2 1 6 5 1 → 3 3 2 7 3 2，从左往右逐条边算 P[i]，让学生看到"左边多出来的人必须穿过这条边"。  
参考：A − B = 2 −1 −1 −1 2 −1，P = 2 1 0 −1 1 0，链上答案 Σ|P[i]| = 2+1+0+1+1+0 = 5。

**第 8 页 · Back to the ring: one extra variable**

提问：为什么 flow[N] = f 也符合公式 P[N] + f？  
答案：因为 ΣA = ΣB，所以 P[N] = 0。

**第 9 页 · Stand at x, step one to the right**

在下方空白画数轴，标出 P = −1 0 0 1 1 2。让学生站在不同位置，算到所有点的距离之和。  
参考答案：站在 −1：0+1+1+2+2+3 = 9；站在 0：1+0+0+1+1+2 = 5；站在 1：2+1+1+0+0+1 = 5；站在 2：3+2+2+1+1+0 = 9。  
最小值 5 出现在 0 和 1 之间（两个中位数之间都可以）。这就是 Greedy：一直往更好的方向走，直到走不动为止。

**第 10 页 · Sample 1**

答案：A − B = 2 −1 −1 −1 2 −1；P = 2 1 0 −1 1 0；排序后 −1 0 0 1 1 2；median 取 1（取 0 也可以）；答案 Σ|P − med| = 5。  
再看样例 2：A = 5 0 0 0 0，B = 1 1 1 1 1，P = 4 3 2 1 0，median = 2，答案 6。如果只能单方向走（f = 0），答案是 10：这就是"环"带来的好处。

**第 11 页 · Prefix sums, then sort for the median**

强调 long long：P 最大可到 10^5 × 10^5 = 10^10。复杂度 O(N log N)，瓶颈是 sort。

**第 12 页 · Subtasks and common mistakes**

挑战题：如果第 i 条边每人收 w[i] 元，中位数还成立吗？  
答案：不能用普通中位数，要用带权中位数（weighted median）：把每个 P[i] 看成权重为 w[i] 的点，取使左右权重平衡的点。

**第 13 页 · Tennis Robot II**

约 25 分钟。Spaceship 的循环在空间上（cabin 围成一圈），这题的循环在时间上（指令一轮一轮重复）。同一个技巧：把一整轮压缩成一个摘要。

**第 14 页 · The problem**

问"三问"中的第 1 问：brute force 是什么？为什么慢？  
答案：直接模拟；最多约 10^6 轮 × 2×10^5 条指令 = 2×10^11 步。慢在"轮数太多"，接下来就要把轮数压缩掉。

**第 15 页 · Summarise one round**

特殊情况：s < 1 表示箱子在第 1 轮就出问题（t = 0）；d[i] ≥ 0 表示箱子永远不会出问题（跳过）；如果没有任何箱子会出问题，输出 FOREVER。  
为什么不用 Binary Search？每个箱子的条件都是关于 r 的一次不等式，可以直接解出来。对 R 二分也可以（条件是单调的），但除法更短，边界情况更少。

**第 16 页 · Same idea: compress the loop**

先让学生口头比较两题，再显示表格。  
参考答案就是表格内容：循环分别在时间上 / 空间上；Prefix Sum 分别求最低点 mn[i] 和净变化 d[i] / 每条边的流量 P[i]；之后分别用除法算轮数再模拟一轮 / 取中位数。

**第 17 页 · Sample 3**

答案：  
箱子 1：指令 1 前变化 0 → mn = 0，d = −1，s = 3 → t = (3 − 1) / 1 + 1 = 3。  
箱子 2：指令 3 前变化 0 → mn = 0，d = 0，s = 2 → 永远不会出问题。  
箱子 3：没被取过，d = +2。  
箱子 4：指令 2 前变化 0，指令 4 前变化 −1 → mn = −1，d = −2，s = 3 → t = (3 − 1) / 2 + 1 = 2。  
箱子 5：没被取过，d = +1。  
所以 R = min(3, 2) = 2。第 3 轮开始时箱子 1 有 1 个、箱子 4 有 0 个。指令 1（1→5）成功；指令 2 要从箱子 4 取球，空了，停下。答案 = 2 × 4 + 1 = 9。  
手动验证箱子 4：第 2 轮最低点 3 − 2 = 1（可以），第 3 轮最低点 3 − 4 = −1（失败）。

**第 18 页 · Rounds by division**

答案最大可到 10^6 × 2×10^5 = 2×10^11，必须用 long long。整数除法向下取整，正好是公式需要的 floor。  
之后：b[i] = x[i] + R·d[i]，从这里模拟一轮，答案 = R·M + 这一轮成功的条数。完整程序见 2024_P5_Tennis_Robot_II.cpp。

**第 19 页 · Atlantis III:Twin Rivers**

约 30 分钟。目标：学生要记住"差分数组 + 一次 prefix sum"能还原分段常数函数（step function），"二阶差分 + 两次 prefix sum"能还原分段线性函数（piecewise-linear function）。

**第 20 页 · The problem**

在右侧画出三条陆地和两条河，用样例 1：River 1 的桥在 2 和 6，River 2 的桥在 4。

**第 21 页 · How long is one trip?**

Brute force：枚举每个 p，再重算所有行程，O(L·T) ≈ 10^11，只能过 subtask 1。  
参考：去 Strip 3 的行程 X = 4，经桥 2 和 4：2 + 2·(4 − 2) = 6；经桥 6 和 4 也是 6。

**第 22 页 · Each trip's cost is a simple shape in p**

两种行程的代价函数都是折线：  
去 Strip 2：V 形 1 + 2|X − p|，在 old 处被截平（新桥离 X 太远就不如旧桥）。  
去 Strip 3：trough（槽形）：在 [u2, X]（或 [X, w2]）上是平底，离开平底每 1 km 增加 2，同样被 old 截平。平底高度是 2 + 2·(X − u2)。  
红点是拐点（转折点）：斜率只在这些地方改变（−2、0、+2 之间切换）。每个行程最多只有几个拐点，这就是后面能用二阶差分的关键。  
具体例子（样例 1，新桥建在 River 1）：行程 X = 4 去 Strip 3：u2 = 4，平底只有一个点，w = 6 6 4 2 4 6 6；行程 X = 3 去 Strip 3：只有右边的 w2 = 4，平底是 [3, 4]、高度 4，w = 6 6 4 4 6 6 6（p = 1..7）。

**第 23 页 · Why not just try every p?**

Brute force：L 约 10^6 个位置 p，每个 p 都要把 2×10^5 个行程的代价加起来，共约 2×10^11 次运算，远远超时（1 秒大约只能做 10^8 次）。  
关键：每个行程的 w(p) 是一条折线，只有少数几个拐点（转折点）。我们只记下拐点处的信息（每个行程 O(1) 个位置），最后用两次 prefix sum 一次性还原出所有 p 上的总代价（O(L)）。再加上每个行程用 Binary Search 找最近的桥 O(log N)，总复杂度 O(T log N + L)，约 2×10^5 × 18 + 10^6 ≈ 5×10^6。  
提问：能不能每个行程只算几个 p？答案：我们要的是"所有行程代价之和"在每个 p 上的值，最小值可能出现在任何 p，所以每个 p 的总和都要知道——但不需要一个 p 一个 p 地去加。  
为了做到这一点，需要两个工具：差分数组（下一页）和二阶差分（再下一页）。

**第 24 页 · Store the jumps, not the values**

差分（difference）就是相邻两项的差：D[i] = a[i] − a[i−1]。它记录的是"在哪里、跳了多少"。  
答案：D = 3 0 0 4 0 0 −5 0；D 的前缀和 = 3 3 3 7 7 7 2 2 = a。差分和 prefix sum 互为逆运算。  
经典用法（区间加）：把 a[2..4] 都加 5 → 只改 D[2] += 5、D[5] −= 5，最后做一次前缀和得到 3 8 8 12 7 7 2 2。每次修改 O(1)，最后还原 O(n)。  
局限：差分数组只在"阶梯形"（分段常数，step function）的数据上省事。如果数据是斜线（每一格都在变），D 处处不为 0，就没有节省了——这就是下一页要讲二阶差分的原因。

**第 25 页 · Store the bends, not the values**

答案：斜率（一阶差分）w(p) − w(p−1)，p = 2..7：0, −2, −2, 2, 2, 0。  
d2（斜率的变化），p = 2..6：−2, 0, 4, 0, −2。只有在拐点 p = 2、4、6 处不为 0。  
为什么？折线在两个拐点之间是直线，斜率不变，所以斜率的差是 0；只有在拐点处斜率才改变。一阶差分（斜率）在斜线上处处不为 0，二阶差分只在拐点不为 0，所以每个行程只需要写 O(1) 个位置。  
还原（两次 prefix sum）：已知 w(0) = 6、w(1) = 6，所以 slope(1) = 0。slope 依次加上 d2：0, −2, −2, 2, 2, 0；w 依次加上 slope：6, 4, 2, 4, 6, 6。和原来的 w 完全一样。  
代码里的 tot[q+1] = 2·tot[q] − tot[q−1] + d2[q] 就是把这两次 prefix sum 合并成一行：tot[q+1] − tot[q] = (tot[q] − tot[q−1]) + d2[q]，即"新斜率 = 旧斜率 + 斜率变化"。

**第 26 页 · Store changes, rebuild with prefix sums**

多个行程怎么办？二阶差分是线性的：总代价的 d2 = 每个行程的 d2 相加。所以所有行程都往同一个 d2 数组里写，最后只还原一次。  
重点讲还原公式：tot[q+1] = 2·tot[q] − tot[q−1] + d2[q]。把它移项：tot[q+1] − tot[q] = (tot[q] − tot[q−1]) + d2[q]，左边是 q 到 q+1 的斜率，括号里是上一段的斜率，d2[q] 是斜率的变化。所以这一行其实就是两次 prefix sum：先累加 d2 得到斜率，再累加斜率得到 tot。需要两个起点 tot[0] 和 tot[1]（代码里的 v0、v1）。  
用样例 1 的行程验证：w(0) = 6、w(1) = 6，d2[1..6] = 0, −2, 0, 4, 0, −2 → w(2) = 2·6 − 6 + 0 = 6，w(3) = 2·6 − 6 − 2 = 4，w(4) = 2·4 − 6 + 0 = 2，w(5) = 2·2 − 4 + 4 = 4，w(6) = 2·4 − 2 + 0 = 6，w(7) = 2·6 − 4 − 2 = 6。  
复杂度从 O(T·L) 降到 O(T log N + L)。  
提问：普通差分数组（一次 prefix sum）能还原什么样的函数？答案：只能还原分段常数函数（step function）。分段线性函数（折线）需要二阶差分 + 两次 prefix sum。

**第 27 页 · Trip X = 4 to Strip 3 (sample 1)**

答案：原代价 Old cost：经桥 2 和 4 → 2 + 2·2 = 6（经桥 6 和 4 也是 6）。  
w(p)，p = 1..7：6 6 4 2 4 6 6。  
d2[p]，p = 2..6：−2, 0, 4, 0, −2（只有转折点 2、4、6 处不为 0）。  
整个样例在 River 1 的 p = 4 建新桥：四个行程的代价是 4、2、4、3 → 总和 13。

**第 28 页 · The big picture before the code**

先讲整体流程，再看代码。程序分 5 步：  
① 读入，把桥按河分开存（每条河的桥排好序）。  
② 对每个行程：用 Binary Search 找 X 左右最近的桥（pred / succ）；写出这个行程的新代价 w(p)，分两种情况：f 表示新桥建在 River 1，g 表示建在 River 2；再用 addFunc 把它加进总和——只在转折点附近写 d2，所以每个行程只写 O(1) 个位置。  
③ build：两次 prefix sum，还原出每个 p 的总代价 tot[w][p]。  
④ 扫一遍所有 p，两条河都看，取最小值。  
⑤ 输出答案。  
提问：循环里每个行程花多少时间？答案：两次二分 O(log N)，加上 O(1) 个转折点。总复杂度 O(T log N + L)。  
提问：④ 里为什么有时不能把新桥建在 River 1？答案：如果有行程要去 Strip 3，而 River 2 上一座桥都没有，这些行程原本就完成不了，新桥必须建在 River 2（样例 3 就是这种情况）。

**第 29 页 · Five steps, three helpers**

伪代码和完整程序 2024_P6_Twin_Rivers.cpp 一一对应：pred / succ 是两个二分函数；trough(a..b) 表示在 [a, b] 上是平底、两边斜率 ±2 的槽形函数，平底高度是 2 + 2·(b − a)；addFunc 只在转折点附近写 d2；build 做两次 prefix sum。  
用样例 1 的行程（X = 4，去 Strip 3）验证：u2 = w2 = 4，所以 f 的两个 trough 都是 [4, 4]、高度 2；old = 6。f(p) = 6 6 4 2 4 6 6（p = 1..7），和手算页的结果一致。  
去 Strip 2 的行程：新桥建在 River 2 对它没有帮助，所以 g = old（常数函数，d2 全是 0）。

**第 30 页 · Write d2, then two prefix sums**

转折点可能落在半整数上（两段函数相交处），所以代码在每个转折点附近多检查几个整数（用 2 倍坐标存）。完整程序：2024_P6_Twin_Rivers.cpp。复杂度 O(T log N + L)。

**第 31 页 · Write Spaceship Shuffle from scratch**

下去巡视。最常见的 bug：用 int 而不是 long long；q 没有从下标 1 开始排序；把 p 原地排序后又拿来用（应该排序一份拷贝）。  
样例答案：样例 1 = 5，样例 2 = 6，样例 3 = 3。

**第 32 页 · Three faces of Prefix Sum**

让每个学生说出今天的一道题，以及它用了哪个技巧。  
参考答案：Spaceship Shuffle：Prefix Sum（每条边的流量）+ Greedy（中位数）；Tennis Robot II：Prefix Sum（一轮的最低点和净变化）+ 除法算轮数；Twin Rivers：二阶差分 + 两次 Prefix Sum，再用 Binary Search 找最近的桥。

**第 33 页 · Homework**

下次课：Binary Search 和 Two Pointers。提醒学生把课程笔记里的 binary search 模板带来。

## AIO Lesson 2: Binary Search + Two Pointers

**第 1 页 · Binary Search + Two Pointers**

第 2 次课的主题是单调性（monotonicity）：它从哪里来，Binary Search 和 Two Pointers 怎样利用它。今天有三种来源：题目直接给的（Laser Cutter）、用前缀最小值造出来的（Space Mission）、用总和造出来的（Lollipops II）。

**第 2 页 · Today's plan**

先用 5 分钟讲上次的作业（Tennis Robot II）：谁的轮数除法公式写对了？  
参考：t = (s − 1) / (−d[i]) + 1，其中 s = X[i] + mn[i]；s < 1 时 t = 0；d[i] ≥ 0 时跳过。

**第 3 页 · Today: the monotone pair**

今天每道题都问同一个问题：单调性从哪里来？是题目给的，还是我们自己造出来的？

**第 4 页 · The while (l &lt;= r) template**

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

## AIO Lesson 3: Greedy and the Water Level

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

## AIO Lesson 4: Sparse Table + Greedy

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

