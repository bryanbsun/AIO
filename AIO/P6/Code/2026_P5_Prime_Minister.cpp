// AIO 2026 P5 - Prime Minister
// 方法：Binary Search on Answer + 水位线（把右半边补到 x）
#include <bits/stdc++.h>
using namespace std;

int n, md;
long long K, a[200010];

// 中位数至少为 x：右半边 a[md..n] 都要补到 x，一共要花多少钱
bool check(long long x){
    long long cost = 0;
    for (int i = md; i <= n; i ++)
        if (a[i] < x){
            cost += x - a[i];
            if (cost > K)
                return false;
        }
    return true;
}

int main(){
    cin >> n >> K;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    md = (n + 1) / 2;                       // 中位数的位置（a 已排好序）

    // 二分：最大的 x，使 check(x) 成立
    long long l = a[md], r = a[md] + K;
    while (l <= r){
        long long mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r << endl;
    return 0;
}
