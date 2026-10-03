#include <bits/stdc++.h>
using namespace std;

int n, k, d[200010], c[200010];

int main(){
    cin >> n >> k;

    for (int i = 1; i < n; i ++)
        cin >> d[i];
    for (int i = 1; i <= n; i ++)
        cin >> c[i];

    int need = 0;
    for (int i = 1; i < n; i ++)
        need += d[i];

    int have = 0, buy = 0;
    int cost = 0;
    for (int i = 1; i < n; i ++){
        buy = min(k - have, need);
        need -= buy;
        have += buy;
        cost += c[i] * buy;

        have -= d[i];
    }

    cout << cost << endl;
    return 0;
}
