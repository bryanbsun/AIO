#include <bits/stdc++.h>
using namespace std;

int     n;
int     main(){
    cin >> n;
    int g, g1 = 0, g2 = 0;
    string found = "NO";
    
    for(int i = 0; i < n; i ++){
        cin >> g;
        if (g == 1)
            g1 ++;
        else if (g == 2)
            g2 ++;
        if (g1 > g2){
            found = "YES";
            break;
        }
    }

    cout << found << endl;

    return 0;
}
