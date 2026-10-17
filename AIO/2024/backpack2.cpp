#include <bits/stdc++.h>
using namespace std;

int n, k, d[200010], c[200010];

int main(){
    cin >> n >> k;

    for (int i = 1; i < n; i ++)
        cin >> d[i];
    for (int i = 1; i <= n; i ++)
        cin >> c[i];

    int cost = 0;
    int i = 1;
    while (i < n){
        int j = i + 1;
        for (; j < n; j ++)
            if (c[j] < c[i])
                break;
        int buy = 0;
        for (int k = i; k <= j - 1; k ++)
            buy += d[k];
        cost += c[i] * buy;
        i = j;
    }

    cout << cost << endl;
    return 0;
}
