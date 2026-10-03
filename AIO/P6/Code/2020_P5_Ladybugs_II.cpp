// AIO 2020 P5 - Ladybugs II
// 方法：最优方案一定是连续 K 只瓢虫（窗口）+ Binary Search（定位起点）+ Sparse Table（区间最小值）
#include <bits/stdc++.h>
using namespace std;

int n, K, q;
long long p[100010];
long long f1[18][100010], f2[18][100010];   // Sparse Table：窗口 [l, l+K-1] 的两种代价（去掉 D 的部分）
int lg[100010];

long long qmin(long long f[][100010], int l, int r){
    int k = lg[r - l + 1];
    return min(f[k][l], f[k][r - (1 << k) + 1]);
}

int main(){
    cin >> n >> K >> q;
    for (int i = 1; i <= n; i ++)
        cin >> p[i];

    // 窗口 l（瓢虫 l .. l+K-1）跨过起点 D 时：
    //   先往左再往右：(D - p[l]) + (p[r] - p[l]) = p[r] - 2p[l] + D
    //   先往右再往左：(p[r] - D) + (p[r] - p[l]) = 2p[r] - p[l] - D
    int w = n - K + 1;                      // 窗口个数
    for (int l = 1; l <= w; l ++){
        f1[0][l] = p[l + K - 1] - 2 * p[l];
        f2[0][l] = 2 * p[l + K - 1] - p[l];
    }
    for (int i = 2; i <= w; i ++)
        lg[i] = lg[i/2] + 1;
    for (int k = 1; (1 << k) <= w; k ++)
        for (int l = 1; l + (1 << k) - 1 <= w; l ++){
            f1[k][l] = min(f1[k-1][l], f1[k-1][l + (1 << (k-1))]);
            f2[k][l] = min(f2[k-1][l], f2[k-1][l + (1 << (k-1))]);
        }

    for (int t = 1; t <= q; t ++){
        long long D;
        cin >> D;

        // 二分：第一只位置 >= D 的瓢虫 s
        int l = 1, r = n;
        while (l <= r){
            int mid = (l + r) / 2;
            if (p[mid] < D)
                l = mid + 1;
            else
                r = mid - 1;
        }
        int s = l;

        long long ans = LLONG_MAX;
        // 窗口全在 D 右边：最好从 s 开始，一直往右走
        if (s <= w)
            ans = min(ans, p[s + K - 1] - D);
        // 窗口全在 D 左边：最好以 s-1 结尾，一直往左走
        if (s - K >= 1)
            ans = min(ans, D - p[s - K]);
        // 窗口跨过 D：l 在 [s-K+1, s-1] 里（还要是合法窗口）
        int lo = max(1, s - K + 1), hi = min(s - 1, w);
        if (lo <= hi){
            ans = min(ans, qmin(f1, lo, hi) + D);
            ans = min(ans, qmin(f2, lo, hi) - D);
        }

        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
