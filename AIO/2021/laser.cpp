#include <bits/stdc++.h>
using namespace std;

int     n;
string  a, b;

int lx{0}, ly{0}, lcp{0}, lp{0}, lcx[200010]{0}, lcy[200010]{0};
int ux{0}, uy{0}, ucp{0}, up{0}, ucx[200010]{0}, ucy[200010]{0};
int ans;

int     main(){
    cin >> n;
    cin >> a >> b;

    for (int i = 0; i < 2*n-1; i ++){
        if (a[i] == 'D')
            ly ++;
        else
            lx ++;
        if (a[i] == 'D' && a[i+1] == 'R'){
            lcx[lcp] = lx;
            lcy[lcp] = ly;
            lcp ++;
        }

        if (b[i] == 'D')
            uy ++;
        else
            ux ++;
        if (b[i] == 'R' && b[i+1] == 'D'){
            ucx[ucp] = ux;
            ucy[ucp] = uy;
            ucp ++;
        }
    }

    ans = 0;
    for (int i = 0; i < ucp; i ++){
        for (int j = 0; j < lcp; j ++)
            if (ucx[i] > lcx[j] && ucy[i] < lcy[j])
               ans = max(ans, min(ucx[i] - lcx[j], lcy[j] - ucy[i]));
    }

    cout << ans << endl;

    return 0;
}