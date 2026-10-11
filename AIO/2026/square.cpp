#include <bits/stdc++.h>
using namespace std;

int     n, k, r[1010], c[1010];
int     rem[1010];

long long   give(int r, int l){
    long long sum = 0;
    for (int i = 1; i <= n; i ++){
        sum += min(k, max(0, rem[i] - l));
    }
    return sum;
}

int     main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i ++)
        cin >> r[i];
    for (int i = 1; i <= n; i ++){
        cin >> c[i];
        rem[i] = c[i];
    }

    for (int i = 1; i <= n; i ++){
        int l = 0, r = k;
        while (l <= r){
            int mid = l + (r-l)/2;
            if (give(mid) > r[i])
                l = mid + 1;
            else 
                r = mid - 1;
        }
        if (l > r){
            cout << "NO" << endl;
            break;
        } 
        for (int j = 1; i <= n; j ++){
            if 
        }
    }


    return 0;
}
