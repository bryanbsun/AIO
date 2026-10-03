// AIO 2024 P6 - Atlantis III: Twin Rivers
// 方法：Binary Search（找最近的桥）+ 二阶差分 / 两次 Prefix Sum（叠加分段线性函数）
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e13;

// trough（槽形函数）：在 [l, r] 上取值 h，离开区间每 1 km 增加 2
struct trough{
    long long l, r, h;
};

// 一个行程的新代价：w(p) = min(old, tr[1], ..., tr[k])
struct func{
    long long old;
    trough tr[3];
    int k;
};

int n, L, T, nb[3];
long long br[3][200010];            // br[1][]：River 1 的桥；br[2][]：River 2 的桥（已排序）
long long x[200010];
int s[200010];
long long d2[3][1000010];           // 二阶差分：[1] 新桥建在 River 1，[2] 建在 River 2
long long v0[3], v1[3];             // 总代价在 p = 0、p = 1 处的值
long long tot[3][1000010];          // 还原出的总代价

long long calc(trough t, long long p){
    long long d = 0;
    if (p < t.l)
        d = t.l - p;
    else if (p > t.r)
        d = p - t.r;
    return t.h + 2 * d;
}

long long calc(func &f, long long p){
    long long v = f.old;
    for (int i = 1; i <= f.k; i ++)
        v = min(v, calc(f.tr[i], p));
    return v;
}

void addTrough(func &f, long long l, long long r, long long h){
    f.k ++;
    f.tr[f.k].l = l;
    f.tr[f.k].r = r;
    f.tr[f.k].h = h;
}

// 向下取整的 b / 2（b 可能是负数）
long long half(long long b){
    if (b >= 0)
        return b / 2;
    return -((-b + 1) / 2);
}

// 把一个行程的函数 f 加到第 w 个累加器
void addFunc(int w, func &f){
    v0[w] += calc(f, 0);
    if (L >= 1)
        v1[w] += calc(f, 1);

    // 转折点（用 2 倍坐标，可能是半整数）
    long long bp[20];
    int cnt = 0;
    for (int i = 1; i <= f.k; i ++){
        trough t = f.tr[i];
        bp[++ cnt] = 2 * t.l;
        bp[++ cnt] = 2 * t.r;
        if (f.old < INF){                       // 和 old 相交的地方
            bp[++ cnt] = 2 * t.l - (f.old - t.h);
            bp[++ cnt] = 2 * t.r + (f.old - t.h);
        }
        for (int j = 1; j <= f.k; j ++)         // 和另一个 trough 相交的地方
            if (i != j){
                bp[++ cnt] = 2 * t.l - (f.tr[j].h - t.h);
                bp[++ cnt] = 2 * t.r + (f.tr[j].h - t.h);
            }
    }

    // 在每个转折点附近取几个整数点，记录二阶差分
    long long pt[80];
    int np = 0;
    for (int i = 1; i <= cnt; i ++){
        long long c = half(bp[i]);
        for (long long q = c - 1; q <= c + 2; q ++)
            if (q >= 1 && q <= L - 1)
                pt[++ np] = q;
    }
    sort(pt + 1, pt + np + 1);
    for (int i = 1; i <= np; i ++){
        if (i > 1 && pt[i] == pt[i-1])          // 去重
            continue;
        long long q = pt[i];
        d2[w][q] += calc(f, q + 1) - 2 * calc(f, q) + calc(f, q - 1);
    }
}

// 两次 prefix sum：由二阶差分还原每个 p 的总代价
void build(int w){
    tot[w][0] = v0[w];
    if (L >= 1)
        tot[w][1] = v1[w];
    for (int q = 1; q + 1 <= L; q ++)
        tot[w][q+1] = 2 * tot[w][q] - tot[w][q-1] + d2[w][q];
}

// 二分：第 w 条河上 <= v 的最大桥，没有返回 -1
long long pred(int w, long long v){
    int l = 1, r = nb[w];
    while (l <= r){
        int mid = (l + r) / 2;
        if (br[w][mid] <= v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (r >= 1)
        return br[w][r];
    return -1;
}

// 二分：第 w 条河上 >= v 的最小桥，没有返回 -1
long long succ(int w, long long v){
    int l = 1, r = nb[w];
    while (l <= r){
        int mid = (l + r) / 2;
        if (br[w][mid] < v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (l <= nb[w])
        return br[w][l];
    return -1;
}

// 去 Strip 3：2 + 2 * (max(x, a, b) - min(x, a, b))
long long span(long long x, long long a, long long b){
    return 2 + 2 * (max(x, max(a, b)) - min(x, min(a, b)));
}

int main(){
    bool hasS3 = false;

    cin >> n >> L;
    for (int i = 1; i <= n; i ++){
        long long b;
        int r;
        cin >> b >> r;
        br[r][++ nb[r]] = b;
    }
    cin >> T;
    for (int j = 1; j <= T; j ++){
        cin >> x[j] >> s[j];
        if (s[j] == 3)
            hasS3 = true;
    }

    for (int j = 1; j <= T; j ++){
        long long u1 = pred(1, x[j]), w1 = succ(1, x[j]);   // River 1 左右最近的桥
        long long u2 = pred(2, x[j]), w2 = succ(2, x[j]);   // River 2 左右最近的桥
        func f, g;
        f.k = g.k = 0;

        if (s[j] == 2){
            long long d = INF;
            if (u1 >= 0)
                d = min(d, x[j] - u1);
            if (w1 >= 0)
                d = min(d, w1 - x[j]);
            f.old = g.old = 1 + 2 * d;
            addTrough(f, x[j], x[j], 1);    // 新桥在 River 1 的 p：1 + 2|x - p|
            addFunc(1, f);
            addFunc(2, g);                  // 新桥在 River 2：这个行程不变
        }else{
            long long old = INF;
            long long c1[3] = {0, u1, w1}, c2[3] = {0, u2, w2};
            for (int a = 1; a <= 2; a ++)
                for (int b = 1; b <= 2; b ++)
                    if (c1[a] >= 0 && c2[b] >= 0)
                        old = min(old, span(x[j], c1[a], c2[b]));
            f.old = g.old = old;
            // 新桥在 River 1 的 p：配合 River 2 左右最近的桥
            if (u2 >= 0)
                addTrough(f, u2, x[j], 2 + 2 * (x[j] - u2));
            if (w2 >= 0)
                addTrough(f, x[j], w2, 2 + 2 * (w2 - x[j]));
            addFunc(1, f);
            // 新桥在 River 2 的 p：配合 River 1 左右最近的桥
            if (u1 >= 0)
                addTrough(g, u1, x[j], 2 + 2 * (x[j] - u1));
            if (w1 >= 0)
                addTrough(g, x[j], w1, 2 + 2 * (w1 - x[j]));
            addFunc(2, g);
        }
    }

    build(1);
    build(2);
    long long ans = -1;
    for (int p = 0; p <= L; p ++){
        // 建在 River 1 时，去 Strip 3 的行程还需要 River 2 上已有桥
        if (!hasS3 || nb[2] > 0)
            if (ans == -1 || tot[1][p] < ans)
                ans = tot[1][p];
        if (ans == -1 || tot[2][p] < ans)
            ans = tot[2][p];
    }

    cout << ans << endl;
    return 0;
}
