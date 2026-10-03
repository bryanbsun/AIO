// AIIO 2023 P1 - Sculpture III
// 方法：DP（dp[i] = 最后一个用的基座是 i）+ 后缀最小值 suffix min + 前缀最大值 prefix max
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long a[100010];
int lim[100010];                // lim[i] = 所有右端点 r >= i 的限制中，最小的左端点 l
long long dp[100010];           // dp[i]：最后一个使用的基座恰好是 i 时的最大美观度
long long best[100010];         // best[i] = max(dp[1..i])，best[0] = 0 表示一个都不选

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];

    // 1) 把每条限制记到右端点上
    for (int i = 1; i <= n + 1; i ++)
        lim[i] = n + 1;
    for (int k = 1; k <= m; k ++){
        int l, r;
        cin >> l >> r;
        lim[r] = min(lim[r], l);
    }

    // 2) 后缀最小值：lim[i] = min(lim[i], lim[i+1])
    for (int i = n - 1; i >= 1; i --)
        lim[i] = min(lim[i], lim[i + 1]);

    // 3) DP：选了 i，上一个被选的 j 必须满足 j < f = min(i, lim[i])
    best[0] = 0;
    for (int i = 1; i <= n; i ++){
        int f = min(i, lim[i]);
        dp[i] = a[i] + best[f - 1];
        best[i] = max(best[i - 1], dp[i]);
    }

    cout << best[n] << endl;
    return 0;
}
