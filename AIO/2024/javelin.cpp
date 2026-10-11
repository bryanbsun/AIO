#include <bits/stdc++.h>
using namespace std;

int n;
int mx;
int d;
int c;

int main(){
    cin >> n;
    for (int i = 0; i < n; i ++){
        cin >> d;
        if (d > mx){
            mx = d;
            c ++;
        }
    }

    cout << c << endl;

    return 0;
}
