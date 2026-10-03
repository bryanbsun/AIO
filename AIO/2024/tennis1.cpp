#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int a[n];
    int b[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        b[i] = a[i];
    }
    int d[m];
    int c[m];
    for(int i = 0; i < m; i++){
        cin >> c[i] >> d[i];
        if(b[c[i] - 1] == 0){
            cout << i + 1;
            return 0;
        }
        b[c[i] - 1]--;
        b[d[i] - 1]++;
    }
    int f[n];
    int min = 10000001;
    for(int i = 0; i < n; i++){
        if(b[i] < 0){
            b[i] = 0;
        }
        f[i] = a[i]/(a[i] - b[i]);
        if(f[i] < min){
            min = f[i];
        }
    }
    for(int i = 0; i < n; i++){
        a[i] = a[i] - f[i]*min;
    }
    for(int i = 0; i < m; i++){
        a[c[i] - 1]--;
        a[d[i] - 1]++;
        if(a[c[i] - 1] <= 0){
            cout << min*m + i + 1;
            return 0;
        }
    }
    cout << "FOREVER";
}
