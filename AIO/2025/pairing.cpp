#include <bits/stdc++.h>
using namespace std;

int n, s, d;
int a, ct[1000010];
int l, h;

int     main(){
    cin >> n >> d >> s;
    l = 1000010; h = 0;

    for (int i = 0; i < n; i ++){
        cin >> a;
        if (a > h)
            h = a;
        if (a < l)
            l = a;
        ct[a] ++;
    }

    while(1){
/*        cout << "[" << l << "," << h << ": ";
        for (int i = l; i <= h; i ++){
            cout << ct[i] << " ";
        }
        cout << "]" << endl;
*/        
        int fd, fs;
        bool skip = false;

        if (l > h){
            cout << "YES" << endl;
            return 0;
        }else{
            if (!ct[l]){
                l ++;
                skip = true;
            }
            if (!ct[h]){
                h --;
                skip = true;
            }
            if (skip) continue;
        }

        if (l + d > h || !ct[l+d])
            fd = 0;
        else{
            fd = l + d;
            if (l+d == l && ct[l+d] < 2)
                fd = 0;
        }
        
        if (l * 2 > s || !ct[s-l])
            fs = 0;
        else{
            fs = s - l;
            if (s-l == l && ct[s-l] < 2)
                fs = 0;
        }
 
        if (!fd && !fs){
            cout << "NO" << endl;
            return 0;
        }else if (!fd && fs){
            ct[l] --;
            ct[fs] --;
        }else if (fd && !fs){
            ct[l] --;
            ct[fd] --;
        }else{
            if (ct[l] && ct[h] && (l + h == s)){
                ct[l] --;
                ct[h] --;
            }else if (ct[h] && h > d && ct[h-d]){
                ct[h] --;
                ct[h-d] --;
            }else{
                cout << "NO" << endl;
                return 0;
            }
        }

    }   
    return 0;
}
