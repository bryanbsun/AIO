// AIO 2022 P6 - Spaceship Shuffle
// Method: Prefix Sum + median
#include <bits/stdc++.h>
using namespace std;

int n;
long long a[100010], b[100010], p[100010], q[100010];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    for (int i = 1; i <= n; i ++)
        cin >> b[i];

    // Prefix Sum: p[i] is the flow on edge i -> i+1 (ignoring the cycle for now)
    for (int i = 1; i <= n; i ++){
        p[i] = p[i-1] + a[i] - b[i];
        q[i] = p[i];
    }

    // cost = sum |p[i] - med|, minimised when med is the median
    sort(q + 1, q + n + 1);
    long long med = q[(n + 1) / 2];

    long long ans = 0;
    for (int i = 1; i <= n; i ++){
        if (p[i] > med)
            ans += p[i] - med;
        else
            ans += med - p[i];
    }

    cout << ans << endl;
    return 0;
}
