#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7fffffff;

int     n, m, h[100010], s[100010], p[100010];
int     bl[100010], br[100010];

int     main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> h[i];
    for (int i = 1; i <= m; i ++)
        cin >> s[i];
    for (int i = 1; i <= m; i ++)
        cin >> p[i];

    fill(bl, bl+n+2, INF);
    fill(br, br+n+2, INF);

    int j = 1;
    for (int i = 1; i <= n; i ++){
        if (bl[i-1] == INF)
            bl[i] = INF;
        else
            bl[i] = bl[i-1] + h[i] - h[i-1];
            
        while(j <= m && s[j] < h[i]){
//            cout << "i: " << i << ", j: " << j << endl;
            bl[i] = min(bl[i], p[j] + h[i] - s[j]);
            j ++;
        }

/*        cout << "L: ";
        for (int p = 1; p < n; p ++)
            cout << bl[p] << ",";
        cout << bl[n] << endl;
*/    }

    j = m;
    for (int i = n; i > 0; i --){
        if (br[i+1] == INF)
            br[i] = INF;
        else
            br[i] = br[i+1] + h[i+1] - h[i];

        while(j >= 1 && s[j] > h[i]){
            br[i] = min(br[i], p[j] + s[j] - h[i]);
            j --;
        }

/*        cout << "R: ";
        for (int p = 1; p < n; p ++)
            cout << br[p] << ",";
        cout << br[n] << endl;
*/    }

    for (int i = 1; i <= n; i ++)
        cout << min(bl[i], br[i]) << " ";
    cout << endl;

    return 0;
}
