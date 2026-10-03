#include <bits/stdc++.h>
using namespace std;

int n, p[100010], up[100010], down[100010], bestup[100010], bestdown[100010];
int answer = n;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> p[i];

    for (int i = 1; i <= n; i ++){
        up[i] = bestup[p[i]-1] + 1;
        bestup[p[i]] = max(bestup[p[i]], up[i]);
    }

    for (int i = n; i >= 1; i --){
        down[i] = bestdown[p[i]-1] + 1;
        bestdown[p[i]] = max(bestdown[p[i]], down[i]);
    }

    int l = 0;
    for (int i = 1; i <= n; i ++)
        l = max(l, min(up[i], down[i]));
    
    answer = n - l * 2 + 1;
    cout << answer << endl;

    return 0;
}