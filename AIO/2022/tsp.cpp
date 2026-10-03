#include <bits/stdc++.h>
using namespace std;

int n, l[100010], r[100010];
int     main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> l[i];
    for (int i = 1; i <= n; i ++)
        cin >> r[i];
    
    for (int i = 2; i <= n; i ++)
        l[i] = max(l[i], l[i-1]);
    for (int i = n-1; i >= 1; i --)
        r[i] = min(r[i], r[i+1]);
    
    for (int i = 1; i < n; i ++)
        if (l[i] > r[i+1]){
            cout << "NO" << endl;
            return 0;
        }
    
    cout << "YES" << endl;
    return 0;
}