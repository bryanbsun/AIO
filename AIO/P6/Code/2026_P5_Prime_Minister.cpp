// AIO 2026 P5 - Prime Minister
// Method: Binary Search on Answer + water level (raise the right half up to x)
#include <bits/stdc++.h>
using namespace std;

int n, md;
long long K, a[200010];

// median at least x: every value in the right half a[md..n] must be raised to x; is the total cost within K?
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
    md = (n + 1) / 2;                       // position of the median (a is already sorted)

    // binary search: the largest x for which check(x) holds
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
