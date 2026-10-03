#include <bits/stdc++.h>
using namespace std;

int     n, a[100010], b[100010];
long long   p[100010], m, ans;

int     main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    for (int i = 1; i <= n; i ++)
        cin >> b[i];
    
    for (int i = 1; i <= n; i ++)
        p[i] = p[i-1] + a[i] - b[i];

    sort(p+1, p+n+1);
    m = p[(n+1)/2];

    for (int i = 1; i <= n; i ++)
        ans += llabs(p[i] - m);
    
    cout << ans <<endl;

    return 0;
}