#include <bits/stdc++.h>
using namespace std;

int     r, c, q, t[20][100010];
int     pours;

bool    ispeak(int x, int y){
    if (t[x][y] > t[x-1][y]
        && t[x][y] > t[x][y-1]
        && t[x][y] > t[x+1][y]
        && t[x][y] > t[x][y+1])
        return true;
    return false;
}

int     main(){
    cin >> r >> c >> q;
    memset(t,-1,sizeof(t));
    for (int i = 1; i <= r; i ++)
        for (int j = 1; j <= c; j ++)
            cin >> t[i][j];

    for (int i = 1; i <= r; i ++)
        for (int j = 1; j <= c; j ++)
            pours += ispeak(i, j);            

    cout << pours << endl;

    int x, y, n;
    for (int i = 0; i < q; i ++){
        cin >> x >> y >> n;
        pours -= ispeak(x, y) + ispeak(x-1, y) + ispeak(x, y-1) + ispeak(x+1, y) + ispeak(x, y+1);
        t[x][y] = n;
        pours += ispeak(x, y) + ispeak(x-1, y) + ispeak(x, y-1) + ispeak(x+1, y) + ispeak(x, y+1);
        cout << pours << endl;
    }

    return 0;
}