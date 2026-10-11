#include <bits/stdc++.h>
using namespace std;

int n, k, c[200010];
int tc;

int main(){
    cin >> n >> k;
    for (int i = 0; i < n; i ++)
        cin >> c[i];

    for (int i = 0; i < k; i ++)
        tc += c[i];
    for (int i = n - 1 - k; i >= k; i -= 2)
        tc += c[i];

    cout << tc << endl;

    return 0;
}
