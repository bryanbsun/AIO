#include <bits/stdc++.h>
using namespace std;

int n, k, c[4][100010];
int answer;

int main(){
    int x;
    cin >> n >> k;
    for (int i = 0; i < n; i ++){
        cin >> x;
        c[i%3][x] ++;
    }

    for (int i = 0; i < 3; i ++){
        sort(c[i],c[i]+k+1,greater<int>());
        answer += n/3 - c[i][0];
    }
    
    cout << answer << endl;
    return 0;
}