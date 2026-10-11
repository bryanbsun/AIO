// AIO 2019 P6 - Lollipops, Sweets and Chocolates II
// Method: Binary Search (on R) + Two Pointers (count the shops for each house)
#include <bits/stdc++.h>
using namespace std;

int n, m;
long long L, sh[100010], ho[100010], s[100010], cnt[100010];

// Two Pointers: with radius R, count how many shops each house can reach; return the sum
long long total(long long R){
    int lo = 1, hi = 1;     // shops [lo, hi) are inside [h-R, h+R]
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

    // even R = L gives a sum below S: no answer
    if (total(L) < S){
        cout << -1 << endl;
        return 0;
    }

    // binary search: the smallest R whose sum >= S
    long long l = 0, r = L;
    while (l <= r){
        long long mid = (l + r) / 2;
        if (total(mid) >= S)
            r = mid - 1;
        else
            l = mid + 1;
    }

    // check: do the sorted counts match s exactly?
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
