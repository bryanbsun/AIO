#include <bits/stdc++.h>
using namespace std;

int b, n, a[100010];

int     main(){
    cin >> b >> n;
    for(int i = 1; i <= b; i ++)
        cin >> a[i];

    memcpy(aa, a, sizeof(a));
    sort(aa+1, aa+b+1)

    int total = 0;
    int p = 0, lastsize = 0;
    while (total < n){
        while(p < b && aa[p] == lastsize)
            p ++;
    }

    cout << p << endl;

    return 0;
}
