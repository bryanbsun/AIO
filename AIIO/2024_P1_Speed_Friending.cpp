// AIIO 2024 P1 - Speed Friending
// 方法：关键观察（最后一个朋友只能是 1 或 N，只需比较左右两边的"最大性格距离"）
//       + 线段树 Segment Tree（单点修改、区间最大值/最小值）
#include <bits/stdc++.h>
using namespace std;

int n, q;
long long p[200010];
long long mx[800010], mn[800010];   // 线段树：节点存区间最大值、最小值
long long qmx, qmn;                 // 一次查询的结果

void update(int node, int l, int r, int pos, long long val){
    if (l == r){
        mx[node] = val;
        mn[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(2 * node, l, mid, pos, val);
    else
        update(2 * node + 1, mid + 1, r, pos, val);
    mx[node] = max(mx[2 * node], mx[2 * node + 1]);
    mn[node] = min(mn[2 * node], mn[2 * node + 1]);
}

// 查询 [ql, qr] 的最大值、最小值，结果放在 qmx、qmn
void query(int node, int l, int r, int ql, int qr){
    if (qr < l || r < ql)
        return;
    if (ql <= l && r <= qr){
        qmx = max(qmx, mx[node]);
        qmn = min(qmn, mn[node]);
        return;
    }
    int mid = (l + r) / 2;
    query(2 * node, l, mid, ql, qr);
    query(2 * node + 1, mid + 1, r, ql, qr);
}

// [l, r] 里所有人与学生 s 的最大性格距离
long long maxDist(int l, int r, int s){
    qmx = -1;
    qmn = 2000000000;
    query(1, 1, n, l, r);
    return max(qmx - p[s], p[s] - qmn);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> p[i];
        update(1, 1, n, i, p[i]);
    }
    cin >> q;
    for (int k = 1; k <= q; k ++){
        int t, s;
        cin >> t >> s;
        if (t == 2){
            long long x;
            cin >> x;
            p[s] = x;
            update(1, 1, n, s, x);
            continue;
        }
        if (s == 1){                    // 左边没人：最后一个一定是 N
            cout << n << "\n";
            continue;
        }
        if (s == n){                    // 右边没人：最后一个一定是 1
            cout << 1 << "\n";
            continue;
        }
        long long L = maxDist(1, s - 1, s);
        long long R = maxDist(s + 1, n, s);
        if (L < R)                      // 左边先被吃完 -> 最后是 N
            cout << n << "\n";
        else if (L > R)                 // 右边先被吃完 -> 最后是 1
            cout << 1 << "\n";
        else                            // 平局：两种结局都可能
            cout << -1 << "\n";
    }
    return 0;
}
