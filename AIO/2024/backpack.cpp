#include <bits/stdc++.h>
using namespace std;

int     n, k, d[200010], c[200010], cheaper[200010], loc[200010];

int     main(){
    cin >> n >> k;
    for (int i = 1; i < n; i ++)
        cin >> d[i];
    for (int i = 1; i <= n; i ++)
        cin >> c[i];

    for (int i = 1; i < n; i ++){
        loc[i+1] = loc[i] + d[i];
    }

    int x[30];

    for (int i = 1; i <= 20; i ++)
        x[i] = n;

    for (int i = n; i > 0; i --){
       for (int j = 1; j < c[i]; j ++)
           x[c[i]] = min(x[c[i]], x[j]);
       cheaper[i] = x[c[i]];
       x[c[i]] = i;
    }
 
    int have = 0;
    int cost = 0;
    int need = 0;
    int buy = 0;
    for (int i = 1; i < n; i ++){
        need = min(loc[cheaper[i]]-loc[i], k);
        buy = max(0, need - have);
        cost += c[i] * buy;
        have += buy;
        have -= d[i];
    }

    cout << cost << endl;

    return 0;
}
