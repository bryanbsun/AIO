#include <bits/stdc++.h>
using namespace std;

int n;
string s;
char letters[5]{'S','N','A','K','E'};

bool    check(int x){
    int i = 0, p = 0, c = 0;
    if (x == 0)
        return true;

    while(i < n && p < 5){
        if (s[i] == letters[p])
            c ++;
        if (c == x){
            c = 0;
            p ++;
        }
        i ++;
    }

//    cout<<"CHECK: " << x << " " << p << endl;
    return (p >= 5);
}

int main(){
    cin >> n;
    cin >> s;

    int l = 0, r = n/5;
    while (l <= r){
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r << endl;
    
    return 0;
}