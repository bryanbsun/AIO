#include <bits/stdc++.h>
using namespace std;
 
int n,l,a[200010];
 
int     main(){
    cin >> n >> l;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
 
    int y = min(a[n], l - a[1]);
    for (int i = 1; i < n; i ++){
        y = min(y, a[i] * 2 + l - a[i + 1]);
        y = min(y, a[i] + 2 * (l - a[i + 1]));
    }
    cout << y << endl;
 
    return 0;
}
