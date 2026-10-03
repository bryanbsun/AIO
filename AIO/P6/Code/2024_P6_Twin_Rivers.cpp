// AIO 2024 P6 - Atlantis III: Twin Rivers
// 方法：Binary Search（找最近的桥）+ 二阶差分 / 两次 Prefix Sum
//
// 思路：
//   新桥建在第 w 条河的位置 p。对每个行程，把"它的代价"看成 p 的函数 f(p)。
//   f(p) 是一条折线，斜率只有 -2、0、+2，拐点只有几个。
//   所有行程的 f 加起来就是总代价。我们不逐个 p 去加，
//   而是只在拐点 q 处记下二阶差分 d2[q]，最后用两次 prefix sum 还原每个 p 的总代价。
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e13;         // 表示"走不通"

int n, L, T;
vector<long long> br[3];            // br[1]、br[2]：两条河上已有的桥（排序后从小到大）
vector<long long> d2[3];            // 二阶差分：[1] 新桥建在 River 1，[2] 建在 River 2
vector<long long> tot[3];           // 还原出的总代价：tot[w][p]

// 当前正在处理的行程
long long X;                        // 出发位置
int S;                              // 目的地：Strip 2 或 Strip 3
long long u1, w1;                   // River 1 上 X 左边、右边最近的桥（没有则为 -1）
long long u2, w2;                   // River 2 上 X 左边、右边最近的桥（没有则为 -1）
long long oldCost;                  // 不建新桥时的最短路程

// 二分：第 r 条河上 <= v 的最大桥，没有返回 -1
long long pred(int r, long long v){
    int l = 0, h = (int)br[r].size() - 1;
    while (l <= h){
        int mid = (l + h) / 2;
        if (br[r][mid] <= v)
            l = mid + 1;
        else
            h = mid - 1;
    }
    if (h >= 0)
        return br[r][h];
    return -1;
}

// 二分：第 r 条河上 >= v 的最小桥，没有返回 -1
long long succ(int r, long long v){
    int l = 0, h = (int)br[r].size() - 1;
    while (l <= h){
        int mid = (l + h) / 2;
        if (br[r][mid] < v)
            l = mid + 1;
        else
            h = mid - 1;
    }
    if (l < (int)br[r].size())
        return br[r][l];
    return -1;
}

// 去 Strip 2：走到 River 1 上的桥 a，过桥，再走回 X
long long way2(long long a){
    if (a < 0)
        return INF;
    return 1 + 2 * abs(X - a);
}

// 去 Strip 3：用 River 1 上的桥 a 和 River 2 上的桥 b
// 要走遍 X、a、b 覆盖的那一段，来回各一次，再加两座桥
long long way3(long long a, long long b){
    if (a < 0 || b < 0)
        return INF;
    long long hi = max(X, max(a, b));
    long long lo = min(X, min(a, b));
    return 2 + 2 * (hi - lo);
}

// f(w, p)：新桥建在第 w 条河的位置 p 时，当前行程的最短路程
long long f(int w, long long p){
    long long c = oldCost;
    if (S == 2 && w == 1)                               // 新桥当 River 1 的桥
        c = min(c, way2(p));
    if (S == 3 && w == 1)                               // 新桥当 River 1 的桥
        c = min(c, min(way3(p, u2), way3(p, w2)));
    if (S == 3 && w == 2)                               // 新桥当 River 2 的桥
        c = min(c, min(way3(u1, p), way3(w1, p)));
    // S == 2 且 w == 2：新桥在 River 2，去 Strip 2 用不上
    return c;
}

// 把当前行程的 f(w, p) 加进第 w 个累加器
void addTrip(int w){
    // 1. 起点的两个值，还原时要用
    tot[w][0] += f(w, 0);
    if (L >= 1)
        tot[w][1] += f(w, 1);

    // 2. 找候选拐点：关键点 key，以及关键点 ± k（f 碰到 oldCost 的地方）
    long long a, b;                                     // 另一条河上 X 左右最近的桥
    if (w == 1){
        a = u2;
        b = w2;
    }else{
        a = u1;
        b = w1;
    }
    vector<long long> key;
    key.push_back(X);
    if (S == 3){
        if (a >= 0)
            key.push_back(a);
        if (b >= 0)
            key.push_back(b);
        if (a >= 0 && b >= 0)
            key.push_back(a + b - X);                   // 两种走法一样长的位置
    }
    long long k = (oldCost - (S - 1)) / 2;              // oldCost = (S - 1) + 2k

    vector<long long> cand;
    for (int i = 0; i < (int)key.size(); i ++){
        cand.push_back(key[i] - k);
        cand.push_back(key[i]);
        cand.push_back(key[i] + k);
    }
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());   // 去重

    // 3. 在每个候选点 q 记下二阶差分（不是拐点的地方，算出来正好是 0）
    for (int i = 0; i < (int)cand.size(); i ++){
        long long q = cand[i];
        if (q < 1 || q > L - 1)
            continue;
        d2[w][q] += f(w, q + 1) - 2 * f(w, q) + f(w, q - 1);
    }
}

// 两次 prefix sum：由二阶差分还原每个 p 的总代价
void build(int w){
    for (int q = 1; q + 1 <= L; q ++)
        tot[w][q+1] = 2 * tot[w][q] - tot[w][q-1] + d2[w][q];
}

int main(){
    cin >> n >> L;
    for (int i = 1; i <= n; i ++){
        long long b;
        int r;
        cin >> b >> r;
        br[r].push_back(b);
    }
    sort(br[1].begin(), br[1].end());
    sort(br[2].begin(), br[2].end());
    for (int w = 1; w <= 2; w ++){
        d2[w].assign(L + 1, 0);
        tot[w].assign(L + 1, 0);
    }

    bool hasS3 = false;
    cin >> T;
    for (int j = 1; j <= T; j ++){
        cin >> X >> S;
        if (S == 3)
            hasS3 = true;

        // 用二分找两条河上 X 左右最近的桥
        u1 = pred(1, X);
        w1 = succ(1, X);
        u2 = pred(2, X);
        w2 = succ(2, X);

        // 不建新桥时的最短路程
        if (S == 2)
            oldCost = min(way2(u1), way2(w1));
        else
            oldCost = min(min(way3(u1, u2), way3(u1, w2)),
                          min(way3(w1, u2), way3(w1, w2)));

        addTrip(1);
        addTrip(2);
    }

    build(1);
    build(2);

    long long ans = -1;
    for (int p = 0; p <= L; p ++){
        // 建在 River 1 时，去 Strip 3 的行程还需要 River 2 上已有的桥
        if (!hasS3 || !br[2].empty())
            if (ans == -1 || tot[1][p] < ans)
                ans = tot[1][p];
        if (ans == -1 || tot[2][p] < ans)
            ans = tot[2][p];
    }
    cout << ans << endl;
    return 0;
}
