#include <bits/stdc++.h>
using namespace std;

int n;
char s[200010];
int c;

int main(){
    cin >> n;
    for (int i = 0; i < n; i ++){
        cin >> s[i];
        if (i == 1 && s[i-1] == '?')
            s[i-1] = s[i];
        else if (i > 0 && s[i] == '?')
            s[i] = s[i-1];
    }

    for (int i = 1; i < n; i ++)
        if (s[i] == s[i-1])
            c ++;

    cout << c << endl;

    return 0;
}
