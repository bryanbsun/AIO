// AIO 2021 P5 - Space Mission
// Method: prefix minimum (build a monotone array) + Binary Search
#include <bits/stdc++.h>
using namespace std;

int n;
long long F, c[100010], pm[100010];     // pm[i] = min(c[1..i]), never increases

int main(){
    cin >> n >> F;
    for (int i = 1; i <= n; i ++)
        cin >> c[i];

    pm[1] = c[1];
    for (int i = 2; i <= n; i ++)
        pm[i] = min(pm[i-1], c[i]);

    int ans = -1;
    for (int j = 2; j <= n; j ++){          // j: the return day
        long long need = F - c[j];          // the most fuel the launch day may cost
        // binary search: the smallest i (1 <= i < j) with pm[i] <= need
        int l = 1, r = j - 1;
        while (l <= r){
            int mid = (l + r) / 2;
            if (pm[mid] <= need)
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (l <= j - 1)                     // found: launch on day l
            ans = max(ans, j - l + 1);
    }

    cout << ans << endl;
    return 0;
}
