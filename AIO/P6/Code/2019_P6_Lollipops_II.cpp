// AIO 2019 P6 - Lollipops, Sweets and Chocolates II
// 方法：Binary Search（二分 R）+ Two Pointers（统计每个房子的商店数）
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long L, sh[100010], ho[100010], s[100010], cnt[100010];

// Two Pointers：半径为 R 时，每个房子能走到几个商店，返回总和
long long total(long long R){
    int lo = 1, hi = 1;     // 商店 [lo, hi) 在 [h-R, h+R] 里
    long long sum = 0;
    for (int i = 1; i <= m; i ++){
        while (hi <= n && sh[hi] <= ho[i] + R)
            hi ++;
        while (lo <= n && sh[lo] < ho[i] - R)
            lo ++;
        cnt[i] = hi - lo;
        sum += cnt[i];
    }
    return sum;
}

int main(){
    long long S = 0;

    cin >> n >> m >> L;
    for (int i = 1; i <= n; i ++)
        cin >> sh[i];
    for (int i = 1; i <= m; i ++)
        cin >> ho[i];
    for (int i = 1; i <= m; i ++){
        cin >> s[i];
        S += s[i];
    }

    // R = L 时总和仍不够 S，无解
    if (total(L) < S){
        cout << -1 << endl;
        return 0;
    }

    // 二分：找最小的 R，使总和 >= S
    long long l = 0, r = L;
    while (l <= r){
        long long mid = (l + r) / 2;
        if (total(mid) >= S)
            r = mid - 1;
        else
            l = mid + 1;
    }

    // 检查：排序后的计数是否和 s 完全一样
    total(l);
    sort(cnt + 1, cnt + m + 1);
    for (int i = 1; i <= m; i ++)
        if (cnt[i] != s[i]){
            cout << -1 << endl;
            return 0;
        }

    cout << l << endl;
    return 0;
}
