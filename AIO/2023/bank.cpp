#include <bits/stdc++.h>
using namespace std;

int     n;
string  t;
int     d, p[1000010];
int     ans;

int main(){
    cin >> n;
    cin >> t;

/*    for (int i = n-1; i >= 0; i --)
        if (t[i] == 'M')
            d ++;
        else
            p[i] = d;

    for (int i = 0; i < n; i ++)
        cout << p[i] << " ";
    cout << endl;
*/
    int s = 1;
    for (int i = 0; i < n; i ++)
        if (t[i] == 'M')
            ans += s;
        else{
            if (n-1-i > s)
                s ++;
            else
                ans += s;
        }
    
    cout << ans << endl;
    return 0;
}
