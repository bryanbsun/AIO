#include <bits/stdc++.h>
using namespace std;

int     n, k, x[100010], t[100010];

int     main(){
    cin >> n >> k;

    for(int i = 0; i < n; i ++){
        cin >> x[i] >> t[i];
        t[i] -= k * x[i];
    }

    sort(t,t+n);

    int ct = 0, maxct = 0, lastt;

    for(int i = 0; i < n; i ++){
        if(i == 0 || t[i] != lastt){
            maxct = max(ct, maxct);
            lastt = t[i];
            ct = 1;
        }else{
            ct ++;
        } 
    }
    maxct = max(ct, maxct);

    cout << maxct << endl;

    return 0;
}
