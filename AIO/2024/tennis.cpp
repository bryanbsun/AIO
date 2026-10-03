#include <bits/stdc++.h>
using namespace std;

long long    n, m, x[200010], x1[200010], a[200010], b[200010], netout[200010], e[200010];

int     main(){
    cin >> n >> m;

    for (int i = 1; i <= n; i ++)
        cin >> x[i];

    for (int i = 1; i <= m; i ++)
        cin >> a[i] >> b[i];

    memcpy(x1, x, sizeof(x));

    for (int i = 1; i <= m; i ++){
        if (x[a[i]] == 0){
            cout << i - 1 << endl;
            return 0;
        }
        x[a[i]] --;
        x[b[i]] ++;

        netout[a[i]] ++;
        if (netout[a[i]] > e[a[i]])
            e[a[i]] = netout[a[i]];
        netout[b[i]] --;
    }
    
    long long  rounds = 1000010;
    bool netfound = false; 
    for (int i = 1; i <= n; i ++){
        if (netout[i] > 0){
            rounds = min(rounds, (x1[i] - e[i]) / netout[i] + 1);
            netfound = true;
        }
    }

    if (!netfound){
        cout << "FOREVER" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i ++){
        if (netout[i] > 0)
            x1[i] -= netout[i] * rounds;
    }

    for (int i = 1; i <= m; i ++){
        if (x1[a[i]] == 0){
            cout << m * rounds + i - 1 << endl;
            return 0;
        }

        x1[a[i]] --;
        x1[b[i]] ++;
    }

    return 0;
}
