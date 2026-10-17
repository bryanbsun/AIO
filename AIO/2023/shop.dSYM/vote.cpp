#include <bits/stdc++.h>
using namespace std;

int n, m;
int v[100010], p[100010];
int votes[100010][100010], counts[100010];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i ++)
        cin >> v[i];
    for (int i = 1; i <= m; i ++)
        cin >> p[i];

    for (int i = 1; i <= m; i ++)
        votes[v[i]][counts[v[i]]++] = i;
    for (int i = 1; i <= n; i ++)
        sort(votes);
    int c1 = counts[1];

    for (int k = 1; k <= m; k ++){
        for (int i = 1; i <= n; i ++)

    }
    return 0;
}