#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main(){
    cin >> n;
    cin >> s;

    int l = 0, r = 0, p = 0;
    for (int i = 0; i < n; i ++){
        char ins = s[i];
        if (ins == 'L')
            l = min(l, --p);
        else if (ins == 'R')
            r = max(r, ++p);
        else if (ins == 'T')
            p = 0;
    }

    cout << r - l + 1 << endl;
    return 0;
}
