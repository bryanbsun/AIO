// AIO 2025 P6 - Robot Writing
// 方法：关键观察（机器人携带最大值，记录序列单调不减）
//       + 按"新值层"推进 + Sparse Table（区间最大值）+ 二分找区间边界
#include <bits/stdc++.h>
using namespace std;

int n, m, t[200010], s[200010];
int sp[18][200010], lg[200010];     // sp[k][i] = max(t[i .. i + 2^k - 1])
int lv[200010], ti[200010], K;      // 第 k 层：值 lv[k]，第一次出现在第 ti[k] 步
int cur[200010], nc;                // 当前层的可行位置
int nxt[200010], nn;                // 下一层的可行位置
int mark[200010];                   // mark[q] = k：q 已经加入第 k 层（去重）

// 区间 [l, r] 的最大值
int qmax(int l, int r){
    int k = lg[r - l + 1];
    return max(sp[k][l], sp[k][r - (1 << k) + 1]);
}

// 从 p 往左扩展：最小的 l，使 t[l..p] 都 <= v
int extendLeft(int p, int v){
    int l = 1, r = p;
    while (l <= r){
        int mid = (l + r) / 2;
        if (qmax(mid, p) <= v)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

// 从 p 往右扩展：最大的 r，使 t[p..r] 都 <= v
int extendRight(int p, int v){
    int l = p, r = n;
    while (l <= r){
        int mid = (l + r) / 2;
        if (qmax(p, mid) <= v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}

// dt 步内能否恰好从 p 走到 q（区间够大，可以来回走消耗时间）
bool check(int p, int q, int dt){
    int d = abs(q - p);
    return d <= dt && (dt - d) % 2 == 0;
}

// 把 q 加入第 k 层（去重）
void add(int q, int k){
    if (mark[q] != k){
        mark[q] = k;
        nxt[++ nn] = q;
    }
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> t[i];
    cin >> m;
    for (int i = 1; i <= m; i ++)
        cin >> s[i];

    // 观察 1：记录序列必须单调不减
    for (int i = 2; i <= m; i ++)
        if (s[i] < s[i-1]){
            cout << "NO" << endl;
            return 0;
        }

    // Sparse Table
    for (int i = 2; i <= n; i ++)
        lg[i] = lg[i/2] + 1;
    for (int i = 1; i <= n; i ++)
        sp[0][i] = t[i];
    for (int k = 1; (1 << k) <= n; k ++)
        for (int i = 1; i + (1 << k) - 1 <= n; i ++)
            sp[k][i] = max(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);

    // 把 s 分层：每个新出现的值是一层
    for (int i = 1; i <= m; i ++)
        if (i == 1 || s[i] != s[i-1]){
            K ++;
            lv[K] = s[i];
            ti[K] = i;
        }

    // 第 1 层（起点）：t[p] = s[1]，按"<= s[1] 的极大区间 [i, j]"处理
    bool start = false;
    int i = 1;
    while (i <= n){
        if (t[i] > lv[1]){
            i ++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && t[j+1] <= lv[1])
            j ++;
        int sz = j - i + 1;
        for (int p = i; p <= j; p ++){
            if (t[p] != lv[1])
                continue;
            if (K == 1){
                // 只有一层：只记录 1 次，或区间至少 2 格可以来回走
                if (m == 1 || sz >= 2)
                    start = true;
                continue;
            }
            // 下一层的目标：区间左右两侧第一个 > lv[1] 的格子
            int dt = ti[2] - ti[1];
            int q = i - 1;
            if (q >= 1 && t[q] == lv[2] && check(p, q, dt) && (p - q == dt || sz >= 2))
                add(q, 2);
            q = j + 1;
            if (q <= n && t[q] == lv[2] && check(p, q, dt) && (q - p == dt || sz >= 2))
                add(q, 2);
        }
        i = j + 1;
    }
    if (K == 1){
        cout << (start ? "YES" : "NO") << endl;
        return 0;
    }

    // 后面每一层
    for (int k = 2; k < K && nn > 0; k ++){
        nc = nn;
        for (int u = 1; u <= nn; u ++)
            cur[u] = nxt[u];
        nn = 0;
        int dt = ti[k+1] - ti[k];
        for (int u = 1; u <= nc; u ++){
            int p = cur[u];
            int l = extendLeft(p, lv[k]), r = extendRight(p, lv[k]);
            if (l - 1 >= 1 && t[l-1] == lv[k+1] && check(p, l - 1, dt))
                add(l - 1, k + 1);
            if (r + 1 <= n && t[r+1] == lv[k+1] && check(p, r + 1, dt))
                add(r + 1, k + 1);
        }
    }

    cout << (nn > 0 ? "YES" : "NO") << endl;
    return 0;
}
