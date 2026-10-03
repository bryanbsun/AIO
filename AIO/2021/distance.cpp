#include <bits/stdc++.h>
using namespace std;

int n, k, d[100010];
int answer;

int main(){
    cin >> n >> k;

    for (int i = 1; i <= n; i ++)
        cin >> d[i];
    
    sort(d+1, d+n+1);

    int lastd = 0;
    for (int i = 1; i <= n; i ++){
        if (i == 1 || d[i] - lastd >= k){
            answer ++;
            lastd = d[i];
        }
    }

    cout << answer << endl;
    
    return 0;
}