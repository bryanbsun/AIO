// AIO 2021 P5 - Space Mission
// 方法：前缀最小值（制造单调性）+ Binary Search
#include <bits/stdc++.h>
using namespace std;

int n;
long long F, c[100010], pm[100010];     // pm[i] = min(c[1..i])，单调不增

int main(){
    cin >> n >> F;
    for (int i = 1; i <= n; i ++)
        cin >> c[i];

    pm[1] = c[1];
    for (int i = 2; i <= n; i ++)
        pm[i] = min(pm[i-1], c[i]);

    int ans = -1;
    for (int j = 2; j <= n; j ++){          // j：返回的那一天
        long long need = F - c[j];          // 出发那天最多能花多少燃料
        // 二分：最小的 i（1 <= i < j），使 pm[i] <= need
        int l = 1, r = j - 1;
        while (l <= r){
            int mid = (l + r) / 2;
            if (pm[mid] <= need)
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (l <= j - 1)                     // 找到了：从第 l 天出发
            ans = max(ans, j - l + 1);
    }

    cout << ans << endl;
    return 0;
}
