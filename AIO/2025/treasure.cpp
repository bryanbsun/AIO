#include <bits/stdc++.h>
using namespace std;

int     n, l;
int     main(){
    cin >> n >> l;
    int s = 1, e = l;
    int a,b;

    for (int i = 0; i < n; i ++){
        cin >> a >> b;
        if (a > s)
            s = a;
        if (b < e)
            e = b;
    }

    cout << (e>=s ? e-s+1 : 0) << endl;

    return 0;
}
