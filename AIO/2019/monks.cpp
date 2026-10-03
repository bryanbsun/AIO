#include <bits/stdc++.h>
using namespace std;

int ans = 0;
int n, s, m, x[100010], st[100010], ms[100010], a[100010];
int main(){
    cin >> n;
    for (int i = 0; i < n; i ++)
        cin >> x[i];
    cin >> s;
    for (int i = 0; i < s; i ++)
        cin >> st[i];
    cin >> m;
    for (int i = 0; i < m; i ++)
        cin >> ms[i];
    
    sort(x, x+n);
    sort(st, st+s);
    sort(ms, ms+m);

    int p = 0;
    for (int i = 0; i < m; i ++){
        while (p < n && (x[p] < ms[i] || a[p] != 0))
            p ++;
        if (p < n){
            ans ++;
            a[p] = 1;
        }
    }
/*    cout << ans << ": ";
    for (int i = 0; i < n; i ++)
        if (a[i])
            cout << i << " ";
        cout << endl;
*/
    p = n - 1;
    for (int i = s-1; i >= 0; i --){
        while (p >= 0 && (x[p] > st[i] || a[p] != 0))
            p --;
        if (p >= 0){
            ans ++;
            a[p] = 1;
        }
    }

/*    cout << ans << ": ";
    for (int i = 0; i < n; i ++)
        if (a[i])
            cout << i << " ";
        cout << endl;
    return 0;
*/

    cout << ans << endl;
    return 0;
}