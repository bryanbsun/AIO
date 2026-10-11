#include <bits/stdc++.h>
using namespace std;

int n, k, ct[100010];

int main(){
    cin >> n >> k;
    int a;
    for (int i = 1; i <= n; i ++){
        cin >> a;
        ct[a] ++;
    }

    int ans = -1;
    for (int i = 1; i <= k; i ++)
        if (ct[i] == 1){
            ans = i;
            break;
        }

    cout << ans << endl;
    return 0;
}
