#include <bits/stdc++.h>
using namespace std;

int n, lo[200010], hi[200010];
string a,b;

bool    check(int x){
//    cout << x << endl;
    for (int i = 0; i <= n - x; i ++)
        if (lo[i] - hi[i+x-1] >= x){
//            cout << i << "-" << i + x << endl;
            return true;
        }
    return false;
}

int     main(){
    cin >> n >> a >> b;

    int x = 0, y = 0;
    for (int i = 0; i < 2*n; i ++)
        if (a[i] == 'R')
            lo[x++] = y;
        else
            y ++;
//    lo[x] = y;

    x = y = 0;
    for (int i = 0; i < 2*n; i ++)
        if (b[i] == 'R')
            hi[x++] = y;
        else
            y ++;
//    hi[x] = y;

//    for (int i = 0; i <= n; i ++)
//        cout << lo[i] << ", " << hi[i] << endl;

    int l = 0, r = n, mid;
    while (l <= r){
        mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r << endl;

    return 0;
}